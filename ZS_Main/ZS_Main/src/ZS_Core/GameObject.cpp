/**
 * Project ZS
 */


#include "GameObject.h"

namespace ZS {

	/**
	 * @brief The base class for all game object
	 * @param _name 
	 * @param _transform 
	 * @param _tag 
	 */
	GameObject::GameObject(std::string _name, Ogre::Transform _transform, Tag _tag) :
		name(_name),
		transform(_transform),
		tag(_tag) {
		
	}

	GameObject::~GameObject() {
		
	}


}
