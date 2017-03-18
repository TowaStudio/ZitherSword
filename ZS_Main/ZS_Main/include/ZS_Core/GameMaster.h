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
#include "MusicUIManager.h"

namespace ZS {
	class GameMaster {

	private:
		static GameMaster* instance;
		GameMaster();
		GameMaster(GameMaster const&) {}
		GameMaster& operator= (GameMaster const&) {}

		InputManager* inputManager;
		LevelManager* levelManager;
		Logger* logger;
		MusicUIManager* musicUIManager;

		int currentLevel; // menu = 0, level
		SaveData tempSave;

	public:
		static GameMaster* GetInstance() {
			return instance;
		}

		LevelManager* getLevelManager() {
			if(!levelManager) {
				//TODO: handle exceptions.
				return nullptr;
			}
			return levelManager;
		}
		void bindLevelManager(LevelManager* _levelManager);

		MusicUIManager* getMusicUIManager() {
			if(!musicUIManager) {
				//TODO: handle exceptions.
				return nullptr;
			}
			return musicUIManager;
		}
		void bindMusicUIManager(MusicUIManager* _musicUIManager);

		InputManager* getInputManager() {
			if(!inputManager) {
				inputManager = new InputManager();
			}

			return inputManager;
		}

		void setLogger(Logger* logger);
		void log(std::string str);
		void log(int content);
		void log(float content);
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