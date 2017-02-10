/**
 * Project ZS
 */


#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Ogre.h"
#include "tinyxml2.h"

namespace ZS
{
	enum Tag {
		Player = 0,
		Enemy = 1 << 0,
		Joint = 1 << 1,
		Item = 1 << 2
	};

	class GameObject {
	public:
		GameObject(std::string name, Ogre::Transform transform, Tag tag);
		~GameObject();

		std::string name;
		Ogre::Transform transform;
		Tag tag;
	};

}

#endif //_GAMEOBJECT_H