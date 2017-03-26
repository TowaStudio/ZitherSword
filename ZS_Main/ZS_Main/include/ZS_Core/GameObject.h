/**
 * Project ZS
 */


#ifndef _ZS_GAMEOBJECT_H
#define _ZS_GAMEOBJECT_H

#include "OgreVector3.h"
#include "Behaviour.h"

namespace ZS
{
	class GameMaster;

	enum Tag {
		PLAYER = 1 << 0,
		ENEMY = 1 << 1,
		ITEM = 1 << 2,
		JOINT = 1 << 3
	};

	class GameObject : public Behaviour {
	protected:
		GameMaster* gm;

	public:
		GameObject(const std::string& name, Tag tag, Vec3 pos, Ogre::Quaternion rot = Ogre::Quaternion::IDENTITY);
		virtual ~GameObject();

		virtual void update(float timeSinceLast) {}

		std::string name;
		Tag tag;
	};

	typedef std::vector<GameObject> GameObjectVec;
}

#endif //_GAMEOBJECT_H