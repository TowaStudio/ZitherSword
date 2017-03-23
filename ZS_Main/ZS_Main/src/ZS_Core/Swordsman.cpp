/**
 * Project ZS
 */


#include "Swordsman.h"
#include "GameMaster.h"
#include "LevelManager.h"


namespace ZS {

	/**
	* Swordsman implementation
	*/
	Swordsman::Swordsman(PlayerStats stats, Vec3 startPos, float startProgress) :
		Unit("Swordsman", Tag::PLAYER, startPos, GameMaster::GetInstance()->getLevelManager()->getUnitID()
		     , stats.hp, stats.maxhp
		     , stats.sp, stats.maxsp
		     , stats.str, stats.def, stats.spd, stats.status, startProgress),
		level(stats.level),
		exp(stats.exp) {

	}

	Swordsman::~Swordsman() {
	}

	/**
	* @return HitInfo
	*/
	HitInfo Swordsman::skill() {
		return HitInfo();
	}

	HitInfo Swordsman::attack() {
		//TODO: Scene Query and get enemy list;
		return HitInfo();
	}

	void Swordsman::heal(float amount) {
		//TODO: Add scene out
		Unit::heal(amount);
	}

	void Swordsman::update(float timeSinceLast) {
		if(isMoving)
			move(timeSinceLast);
		//GameMaster::GetInstance()->log(Ogre::StringConverter::toString(this->pos.x));
	}
}
