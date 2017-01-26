/**
 * Project ZS
 */


#include "GameObject.h"

namespace ZS {

	/**
	 * \brief 
	 * \param name 
	 * \param transform 
	 * \param tag 
	 */
	GameObject::GameObject(string _name, Ogre::Transform _transform, Tag _tag) :
		name(_name),
		transform(_transform),
		tag(_tag) {
		
	}

	GameObject::~GameObject() {
		
	}


}
