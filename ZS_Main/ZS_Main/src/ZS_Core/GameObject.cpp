/**
 * Project ZS
 */


#include "GameObject.h"

namespace ZS {

	/**
	 * @brief The base class for all game object
	 * @param _name 
	 * @param _tag 
	 */
	GameObject::GameObject(const std::string& _name, Tag _tag, Vec3 _pos) :
		name(_name),
		tag(_tag),
		pos(_pos)
	{
		
	}

	GameObject::~GameObject() {
		
	}


}
