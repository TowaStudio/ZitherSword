#include "Weapon.h"
#include "OgreStringConverter.h"

namespace ZS {
	Weapon::Weapon(int _id, float _atk, float _rate, float _range) :
		Item("Weapon" + Ogre::StringConverter::toString(_id), _id),
		atk(_atk), rate(_rate), range(_range)
	{

	}

	Weapon::~Weapon() {
	}
}
