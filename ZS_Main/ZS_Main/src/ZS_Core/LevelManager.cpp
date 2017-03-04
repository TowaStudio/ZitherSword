/**
 * Project ZS
 */

#include "LevelManager.h";
#include "GameMaster.h"
#include "Enemy.h"

namespace ZS {

	LevelManager::LevelManager(int _level) :
		level(_level),
		unitsCount(0),
		jointCount(0),
		swordsman(nullptr)
	{
		
	}

	LevelManager::~LevelManager() {

	}

	int LevelManager::getUnitID() {
		return unitsCount++;
	}

	int LevelManager::getJointID() {
		return jointCount++;
	}

	Swordsman* LevelManager::GetSwordsman() const {
		return swordsman;
	}

	/**
	* @return bool
	*/
	void LevelManager::loadLevel() {
		//TODO: Load scene and enemy profile;
		//level;

		initLevel();
	}

	void LevelManager::initLevel() {
		//TODO: Create Objects and setup player, input;
		Vec3 pos = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 enemyPos = Vec3(5.0f, 0.0f, 0.0f);

		GameMaster* gm = GameMaster::GetInstance();
		
		swordsman = new Swordsman(gm->getPlayerStats(), pos);
		Enemy* enemyA = new Enemy("E1", enemyPos, 100.0f, 100.0f, 20.0f, 20.0f, 100.0f, 20.0f, 12.0f, Status::Normal, 200);
		enemyA->attack();

		gm->log(Ogre::StringConverter::toString(swordsman->hp) + "/" + Ogre::StringConverter::toString(swordsman->maxhp));
		startLevel();
	}

	

	void LevelManager::startLevel() {
		//TODO: Start audio system and input manager;


	}
}
