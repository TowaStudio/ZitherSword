#ifndef _ZS_GAMEUIMANAGER_H
#define _ZS_GAMEUIMANAGER_H
#include "OgreOverlay.h"

namespace ZS {
	class GameUIManager {
	public:
		GameUIManager();
		~GameUIManager();

		Ogre::v1::Overlay* createGameUI();


	};
}

#endif
