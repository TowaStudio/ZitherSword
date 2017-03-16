#ifndef _ZS_PATHFOLLOWHELPER_H
#define _ZS_PATHFOLLOWHELPER_H
#include "Unit.h"
#include "Path.h"

namespace ZS {
	class PathFollowHelper {
	public:
		Unit* unit;
		Path* path;
		float currentProgress;

		PathFollowHelper(Unit* _unit, Path* _path);
		~PathFollowHelper();

		void updateCurrentProgress(float _progress);

		Vec3 getNextPos();
	};
}

#endif
