/**
 * Project ZS
 */


#include "GameMaster.h"

namespace ZS {
	GameMaster* GameMaster::instance = new GameMaster();
	InputManager* GameMaster::inputManager = nullptr;
	LevelManager* GameMaster::levelManager = nullptr;

	/**
	* GameMaster implementation
	*/


	GameMaster::GameMaster() :
		logger(nullptr)
	{
		
	}

	void GameMaster::setLogger(Logger* _logger) {
		logger = _logger;
	}

	void GameMaster::log(std::string str) {
		logger->log(str);
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