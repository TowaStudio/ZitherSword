/**
 * Project ZS
 */


#include "GameMaster.h"

namespace ZS {
	GameMaster* GameMaster::instance = new GameMaster();

	/**
	* GameMaster implementation
	*/


	GameMaster::GameMaster() {
	}

	/**
	* @return bool
	*/
	bool GameMaster::save() {
		return false;
	}

	/**
	* @return SaveData
	*/
	SaveData GameMaster::load() {
		return SaveData();
	}

	void GameMaster::loadStatsConfiguration() {
	}
};