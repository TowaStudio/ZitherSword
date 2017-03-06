/**
 * Project ZS
 */


#ifndef _ZS_GAMEOBJECT_H
#define _ZS_GAMEOBJECT_H

#include "OgreVector3.h"
#include "tinyxml/tinyxml2.h"
#include <string>
#include "Behaviour.h"

namespace ZS
{
	typedef Ogre::Vector3 Vec3;

	enum Tag {
		PLAYER = 1 << 0,
		ENEMY = 1 << 1,
		ITEM = 1 << 2,
		JOINT = 1 << 3
	};

	class GameObject : public Behaviour {
	public:
		GameObject(const std::string& name, Tag tag, Vec3 pos);
		virtual ~GameObject();

		virtual void update(float timeSinceLast) {}

		std::string name;
		Tag tag;
		Vec3 pos;
	};

	typedef std::vector<GameObject> GameObjectVec;
}

#endif //_GAMEOBJECT_H