#include "PathPoint.h"

namespace ZS {
	PathPoint::PathPoint(Vec3 _pos):
		pos(_pos), distanceToNext(0.0f),
		next(nullptr),
		hasTrigger(false), trigger(nullptr)
	{

	}

	PathPoint::~PathPoint() {
	}


	void PathPoint::addTrigger(Trigger* _trigger) {
		trigger = _trigger;
		hasTrigger = true;
	}
}
