/**
 * Project ZS
 */


#include "GameMaster.h"

namespace ZS {
	GameMaster* GameMaster::instance = new GameMaster();

	/**
	* GameMaster implementation
	*/


	GameMaster::GameMaster() :
		inputManager(nullptr),
		levelManager(nullptr),
		logger(nullptr),
		currentLevel(-1),
		tempSave(SaveData())
	{
		
	}

	void GameMaster::bindLevelManager(LevelManager * _levelManager) {
		levelManager = _levelManager;
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
		SaveData save(0, PlayerStats(1, 0, 300.0f, 300.0f, 40.0f, 40.0f, 100.0f, 20.0f, 40.0f, Status::Normal));
		//TODO: File system, load save data.
		tempSave = save;

		return save;
	}

	PlayerStats GameMaster::getPlayerStats() {
		return tempSave.stats;
	}

	void GameMaster::mainMenu() {
		if(currentLevel > 0) {
			delete inputManager;
			delete levelManager;
		}

		//TODO: Load main menu.

		currentLevel = 0;
	}

	void GameMaster::loadLevel(int level) {
		levelManager->loadLevel(0); //TODO
		currentLevel = level;
	}

};