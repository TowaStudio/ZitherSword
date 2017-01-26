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
		Unit("Swordsman", Ogre::Transform(), Tag::Player, LevelManager::GetInstance()->getUnitID(),  {

	}

	/**
	* @return HitInfo
	*/
	HitInfo* Swordsman::skill() {
		return nullptr;
	}
}
