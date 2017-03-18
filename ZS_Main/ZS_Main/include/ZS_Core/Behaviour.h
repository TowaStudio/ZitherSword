#ifndef _ZS_BEHAVIOUR_H
#define _ZS_BEHAVIOUR_H

#include "OgreVector3.h";

namespace ZS {
	typedef Ogre::Vector3 Vec3;

	class Behaviour abstract {
	public:
		Vec3 pos;

		Behaviour(Vec3 _pos) :
			pos(_pos)
		{
			
		}
		virtual ~Behaviour() {}

		virtual void update(float timeSinceLast) {}
	};
}

#endif
