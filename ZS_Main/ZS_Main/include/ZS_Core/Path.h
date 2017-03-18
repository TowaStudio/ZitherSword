#ifndef _ZS_PATH_H
#define _ZS_PATH_H
#include "GameObject.h"

namespace ZS {
	struct PathPoint {
	public:
		Vec3 pos;
		float distanceToNext;
		PathPoint* next;

		PathPoint(Vec3 _pos) :
			pos(_pos), distanceToNext(0.0f),
			next(nullptr)
		{
			
		}
	};

	typedef std::vector<PathPoint*> PointVec;

	class Path {
	public:
		PointVec* pointVec;
		int pointCount;
		float totalLength;

		Path();
		Path(PointVec* points);
		~Path(){}

		void addPoint(Vec3 pointPosition);
		
		Vec3 getPosInSegment(int indexOfStartPoint, float pos);
		Vec3 getPosInPath(float pos, bool referInSegment = false);
		PathPoint* getPoint(int index);
	};
}

#endif
