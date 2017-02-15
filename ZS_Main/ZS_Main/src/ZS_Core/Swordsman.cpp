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
	Swordsman::Swordsman(PlayerStats stats) :
		Unit("Swordsman", Tag::Player, Vec3(0.0f, 0.0f, 0.0f), GameMaster::GetLevelManager()->getUnitID()
			, 0.0f, 0.0f
			, 0.0f, 0.0f
			, 0.0f, 0.0f, 0.0f) {

	}

	/**
	* @return HitInfo
	*/
	HitInfo* Swordsman::skill() {
		return nullptr;
	}
}
