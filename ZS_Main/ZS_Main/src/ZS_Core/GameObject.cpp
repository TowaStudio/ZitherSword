/**
 * Project ZS
 */
#include "GameObject.h"
#include "GameMaster.h"

namespace ZS {

	/**
	 * @brief The base class for all game object
	 * @param _name 
	 * @param _tag 
	 */
	GameObject::GameObject(const std::string& _name, Tag _tag, Vec3 _pos, Ogre::Quaternion _rot) :
		Behaviour(_pos, _rot),
		gm(GameMaster::GetInstance()),
		name(_name), tag(_tag)
	{
		
	}

	GameObject::~GameObject() {
		
	}


}
