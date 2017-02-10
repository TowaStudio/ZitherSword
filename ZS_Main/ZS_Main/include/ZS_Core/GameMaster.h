/**
 * Project ZS
 */


#ifndef _GAMEMASTER_H
#define _GAMEMASTER_H

#include "SaveData.h";
#include "Logger.h";
#include "Stats.h";

namespace ZS {
	class GameMaster {

	private:
		static GameMaster* instance;
		GameMaster();
		GameMaster(GameMaster const&) {};
		GameMaster& operator= (GameMaster const&) {};


	public:
		static GameMaster* GetInstance() {
			return instance;
		}

		bool save();
		SaveData load();

		void loadStatsConfiguration();
		

	};
}

#endif //_GAMEMASTER_H