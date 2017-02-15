/**
 * Project ZS
 */


#ifndef _SAVEDATA_H
#define _SAVEDATA_H

#include "PlayerStats.h"

namespace ZS {

	struct SaveData {
	public:
		SaveData() : 
			levelProgress(0),
			stats(PlayerStats()) {}

		SaveData(int _levelProgress, PlayerStats _stats) : 
			levelProgress(_levelProgress),
			stats(_stats) {}

		int levelProgress;
		PlayerStats stats;
	};
};

#endif //_SAVEDATA_H
