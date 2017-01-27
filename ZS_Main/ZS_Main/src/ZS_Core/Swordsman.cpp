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
		Unit("Swordsman", Ogre::Transform(), Tag::Player, LevelManager::GetInstance()->getUnitID()
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
