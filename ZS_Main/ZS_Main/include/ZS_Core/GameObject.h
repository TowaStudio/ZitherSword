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
		Player = 1 << 0,
		Enemy = 1 << 1,
		Item = 1 << 2,
		Joint = 1 << 3
	};

	class GameObject {
	public:
		GameObject(std::string name, Tag tag, Vec3 pos);
		~GameObject();

		std::string name;
		Tag tag;
		Vec3 pos;
	};

	typedef std::vector<GameObject> GameObjectVec;
}

#endif //_GAMEOBJECT_H