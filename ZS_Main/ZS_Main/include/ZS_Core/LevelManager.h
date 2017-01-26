/**
 * Project ZS
 */


#ifndef _LEVELMANAGER_H
#define _LEVELMANAGER_H

namespace ZS {
	class LevelManager {
	private:
		static LevelManager* instance;
		LevelManager();
		LevelManager(LevelManager const&) {};
		LevelManager& operator= (LevelManager const&) {};

		int unitsCount;
		int jointCount;

	public:
		static LevelManager* GetInstance() {
			return instance;
		}

		int getUnitID();
		int getJointID();

		int level;

		bool loadLevel();

		bool initLevel();

		bool startLevel();
	};

}

#endif //_LEVELMANAGER_H
