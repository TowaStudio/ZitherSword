#include "PathFollowHelper.h"

namespace ZS {
	PathFollowHelper::PathFollowHelper(Unit* _unit, Path* _path):
		unit(_unit),
		path(_path) {
		currentProgress = 0.0f;
	}

	PathFollowHelper::~PathFollowHelper() {
	}

	void PathFollowHelper::updateCurrentProgress(float _progress) {
		currentProgress = _progress;
	}

	Vec3 PathFollowHelper::getNextPos() {
		float step = unit->spd / path->totalLength;
		if(step < 0.0f) { step = 0.0f; }
		currentProgress = std::min(currentProgress + step, 1.0f);
		return path->getPosInPath(currentProgress);
	}
}
