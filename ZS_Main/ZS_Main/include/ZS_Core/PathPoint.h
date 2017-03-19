#ifndef _ZS_PATHPOINT_H
#define _ZS_PATHPOINT_H
#include "OgreVector3.h"
#include "Trigger.h"

namespace ZS {
	typedef Ogre::Vector3 Vec3;

	class PathPoint {
	public:
		Vec3 pos;
		float distanceToNext;
		PathPoint* next;

		bool hasTrigger;
		Trigger* trigger;

		PathPoint(Vec3 _pos);
		~PathPoint();

		void addTrigger(Trigger* _trigger);
	};

	typedef std::vector<PathPoint*> PointVec;
}

#endif
