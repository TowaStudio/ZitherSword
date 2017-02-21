/**
 * Project ZS
 */


#ifndef _ZS_GAMEMASTER_H
#define _ZS_GAMEMASTER_H

#include "InputManager.h"
#include "LevelManager.h"
#include "SaveData.h"
#include "Logger.h"
#include "Stats.h"
#include "AudioSystem.h"

namespace ZS {
	class GameMaster {

	private:
		static GameMaster* instance;
		GameMaster();
		GameMaster(GameMaster const&) {};
		GameMaster& operator= (GameMaster const&) {};

		InputManager* inputManager;
		LevelManager* levelManager;
		Logger* logger;

		int currentLevel; // menu = 0, level
		SaveData tempSave;

	public:
		static GameMaster* GetInstance() {
			return instance;
		}

		LevelManager* getLevelManager() {
			if(!levelManager) {
				levelManager = new LevelManager(-1);
			}

			return levelManager;			
		}

		InputManager* getInputManager() {
			if(!inputManager) {
				inputManager = new InputManager();
			}

			return inputManager;
		}

		void setLogger(Logger* logger);
		void log(std::string str);

		// Save
		bool save();
		SaveData load();
		PlayerStats getPlayerStats();

		// Scenes
		void mainMenu();
		void loadLevel(int level);
		

	};
}

#endif //_GAMEMASTER_H