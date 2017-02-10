/**
 * Project ZS
 */

#include "Unit.h"

namespace ZS {
	Unit::Unit(std::string _name, Ogre::Transform _transform, Tag _tag,
			int _id, float _hp, float _maxhp, float _sp, float _maxsp, float _str, float _def, float _spd) :
		GameObject(_name, _transform, _tag), id(_id),
		hp(_hp), maxhp(_maxhp),
		sp(_sp), maxsp(_maxsp),
		str(_str), def(_def), spd(_spd) {
	}

	Unit::~Unit() {
	}

	/**
	  * @return HitInfo
	  */
	HitInfo* Unit::attack() {
		return nullptr;
	}

	/**
	 * @return bool
	 */
	bool Unit::damage(float dmg) {
		hp -= dmg;
		if(hp <= 0.0f) {
			return true;
		}
		return false;
	}

	/**
	 * @return void
	 */
	void Unit::heal() {
		return;
	}

	
}