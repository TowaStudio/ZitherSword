/**
 * Project ZS
 */

#include "LevelManager.h"

namespace ZS {
	LevelManager* LevelManager::instance = new LevelManager();
	/**
	* LevelManager implementation
	*/

	LevelManager::LevelManager() {
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
