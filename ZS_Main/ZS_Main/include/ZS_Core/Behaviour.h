#ifndef _ZS_BEHAVIOUR_H
#define _ZS_BEHAVIOUR_H

#include "OgreVector3.h"

namespace ZS {
	typedef Ogre::Vector3 Vec3;

	class Behaviour abstract {
	public:
		Vec3 pos;
		Ogre::Quaternion rot;

		Behaviour(Vec3 _pos) :
			pos(_pos), rot(Ogre::Quaternion::IDENTITY) {}
		Behaviour(Vec3 _pos, Ogre::Quaternion _rot) :
			pos(_pos), rot(_rot) {}
		virtual ~Behaviour() {}

		virtual void update(float timeSinceLast) {}
	};
}

#endif
