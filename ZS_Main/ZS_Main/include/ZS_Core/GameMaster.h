/**
 * Project ZS
 */


#ifndef _GAMEMASTER_H
#define _GAMEMASTER_H

#include "InputManager.h"
#include "LevelManager.h"
#include "SaveData.h"
#include "Logger.h"
#include "Stats.h"

namespace ZS {
	class GameMaster {

	private:
		static GameMaster* instance;
		GameMaster();
		GameMaster(GameMaster const&) {};
		GameMaster& operator= (GameMaster const&) {};

		static InputManager* inputManager;
		static LevelManager* levelManager;
		Logger* logger;

	public:
		static GameMaster* GetInstance() {
			return instance;
		}

		static LevelManager* GetLevelManager() {
			if(!levelManager) {
				levelManager = new LevelManager(-1);
			}

			return levelManager;			
		}

		static InputManager* GetInputManager() {
			if(!inputManager) {
				inputManager = new InputManager();
			}

			return inputManager;
		}

		void setLogger(Logger* logger);
		void log(std::string str);

		bool save();
		SaveData load();

		void loadStatsConfiguration();
		

	};
}

#endif //_GAMEMASTER_H