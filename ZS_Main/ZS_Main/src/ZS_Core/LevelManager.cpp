/**
 * Project ZS
 */

#include "LevelManager.h";

namespace ZS {

	LevelManager::LevelManager(int _level) :
		level(_level),
		unitsCount(0),
		jointCount(0)
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

	/**
	* @return bool
	*/
	bool LevelManager::loadLevel() {
		return false;
	}

	/**
	* @return bool
	*/
	bool LevelManager::initLevel() {
		return false;
	}

	/**
	* @return bool
	*/
	bool LevelManager::startLevel() {
		return false;
	}
}
