/**
 * Project ZS
 */


#ifndef _LEVELMANAGER_H
#define _LEVELMANAGER_H

namespace ZS {
	class LevelManager {
	private:
		int level;
		int unitsCount;
		int jointCount;

	public:
		LevelManager(int level);
		~LevelManager();

		int getUnitID();
		int getJointID();

		bool loadLevel();

		bool initLevel();

		bool startLevel();
	};

}

#endif //_LEVELMANAGER_H
