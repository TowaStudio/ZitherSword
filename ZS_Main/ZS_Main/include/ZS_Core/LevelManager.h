/**
 * Project ZS
 */


#ifndef _ZS_LEVELMANAGER_H
#define _ZS_LEVELMANAGER_H
#include "Swordsman.h"

namespace ZS {
	class LevelManager {
	private:
		int level;
		int unitsCount;
		int jointCount;
		Swordsman* swordsman;

	public:
		LevelManager(int level);
		~LevelManager();

		int getUnitID();
		int getJointID();

		Swordsman* GetSwordsman() const;

		void loadLevel();
		void initLevel();
		void startLevel();
	};

}

#endif //_LEVELMANAGER_H
