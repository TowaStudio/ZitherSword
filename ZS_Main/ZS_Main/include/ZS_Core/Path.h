#ifndef _ZS_PATH_H
#define _ZS_PATH_H
#include "GameObject.h"
#include "PathPoint.h"

namespace ZS {
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
		int getIndexFromPos(float _pos);
		PathPoint* getPoint(int index);
	};
}

#endif
