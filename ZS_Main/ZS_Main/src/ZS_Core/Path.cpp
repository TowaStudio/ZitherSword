#include "Path.h"
#include "OgreException.h"
#include "GameMaster.h"

namespace  ZS {
	Path::Path() :
		pointCount(0), totalLength(0.0f)
	{
		pointVec = new PointVec();
	}

	Path::Path(PointVec* points) :
		pointCount(0), totalLength(0.0f)
	{
		pointVec = points;
	}

	void Path::addPoint(Vec3 pointPosition) {
		auto newPoint = new PathPoint(pointPosition);
		pointVec->push_back(newPoint);
		++pointCount;

		// Update the link & length
		if(pointVec->size() > 1) {
			PathPoint* lastPoint = pointVec->at(pointCount - 2);
			lastPoint->next = newPoint;

			float distance = lastPoint->pos.distance(newPoint->pos);
			lastPoint->distanceToNext = distance;
			totalLength += distance;
		}
	}

	Vec3 Path::getPosInSegment(int indexOfStartPoint, float pos) {
		if(pointCount < 2) {
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "No enough points in the path", "Path");
		}

		Vec3 position = Vec3::ZERO;
		PathPoint* startPoint = pointVec->at(indexOfStartPoint);
		PathPoint* endPoint = pointVec->at(indexOfStartPoint+1);

		if(startPoint && endPoint) {
			if(pos > 1.0f) return endPoint->pos;
			if(pos < 0.0f) return startPoint->pos;
			position = pos * endPoint->pos + (1.0f - pos) * startPoint->pos;
		}

		return position;
	}

	Vec3 Path::getPosInPath(float pos, bool referInSegment) {
		if(pointCount < 2) {
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "No enough points in the path", "Path");
		}

		Vec3 position = Vec3::ZERO;

		if(pos >= 1.0f) return pointVec->at(pointCount - 1)->pos;
		if(pos <= 0.0f) return pointVec->at(0)->pos;

		int indexOfStartPoint = -1;
		float segmentPos = 0.0f;

		if(!referInSegment) {
			float distanceFromStart = pos * totalLength;
			
			// Find the reference path point (in length-weighted segment)
			float accDistance = 0.0f;
			while(accDistance < distanceFromStart) {
				++indexOfStartPoint;
				accDistance += pointVec->at(indexOfStartPoint)->distanceToNext;
			}
			// index
			float remainDistanceInSegment = accDistance - distanceFromStart;
			segmentPos = 1.0f - remainDistanceInSegment / pointVec->at(indexOfStartPoint)->distanceToNext;

			return getPosInSegment(indexOfStartPoint, segmentPos);
		} else {
			float segmentLength = 1.0f / static_cast<float>(pointCount - 1);
			
			// Find the reference path point (in equally weighted segment)
			float accDistance = 0.0f;
			while(accDistance < pos) {
				++indexOfStartPoint;
				accDistance += segmentLength;
			}
			float remainDistanceInSegment = accDistance - pos;
			segmentPos = 1.0f - remainDistanceInSegment / segmentLength;

			return getPosInSegment(indexOfStartPoint, segmentPos);
		}
	}

	int Path::getIndexFromPos(float pos) {
		int indexOfStartPoint = -1;
		float distanceFromStart = pos * totalLength;

		float accDistance = 0.0f;
		while(accDistance < distanceFromStart) {
			++indexOfStartPoint;
			accDistance += pointVec->at(indexOfStartPoint)->distanceToNext;
		}
		return indexOfStartPoint;
	}

	float Path::getSegmentPosFromPos(float pos) {
		int indexOfStartPoint = -1;
		float distanceFromStart = pos * totalLength;

		// Find the reference path point (in length-weighted segment)
		float accDistance = 0.0f;
		while(accDistance < distanceFromStart) {
			++indexOfStartPoint;
			accDistance += pointVec->at(indexOfStartPoint)->distanceToNext;
		}
		// index
		float remainDistanceInSegment = accDistance - distanceFromStart;
		float segmentPos = static_cast<float>(indexOfStartPoint) + 1.0f - remainDistanceInSegment / pointVec->at(indexOfStartPoint)->distanceToNext;
		segmentPos = segmentPos / static_cast<float>(pointCount - 1);

		return segmentPos;
	}

	PathPoint* Path::getPoint(int index) {
		if(pointCount > 0)
			return pointVec->at(index);
		else
			return nullptr;
	}
}
