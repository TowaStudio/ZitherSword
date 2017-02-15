/**
 * Project ZS
 */


#ifndef _ZS_GAMEOBJECT_H
#define _ZS_GAMEOBJECT_H

#include "OgreVector3.h"
#include "tinyxml2.h"
#include <string>

namespace ZS
{
	typedef Ogre::Vector3 Vec3;

	enum Tag {
		PLAYER = 1 << 0,
		ENEMY = 1 << 1,
		ITEM = 1 << 2,
		JOINT = 1 << 3
	};

	class GameObject {
	public:
		GameObject(const std::string& name, Tag tag, Vec3 pos);
		virtual ~GameObject();

		std::string name;
		Tag tag;
		Vec3 pos;
	};

	typedef std::vector<GameObject> GameObjectVec;
}

#endif //_GAMEOBJECT_H