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
	Swordsman::Swordsman(PlayerStats stats, Vec3 startPos) :
		Unit("Swordsman", Tag::PLAYER, startPos, GameMaster::GetInstance()->getLevelManager()->getUnitID()
			 , stats.hp, stats.maxhp
			 , stats.sp, stats.maxsp
			 , stats.str, stats.def, stats.spd, stats.status),
		level(stats.level),
		exp(stats.exp)
	{
		
	}

	Swordsman::~Swordsman() {
	}

	/**
	* @return HitInfo
	*/
	HitInfo* Swordsman::skill() {
		return nullptr;
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
		move(moveVec * timeSinceLast);
		GameMaster::GetInstance()->log(Ogre::StringConverter::toString(this->pos.x));
	}
}
