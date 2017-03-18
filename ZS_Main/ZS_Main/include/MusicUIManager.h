#ifndef _ZS_MUSICUIMANAGER_H
#define _ZS_MUSICUIMANAGER_H

#include "OgreOverlayContainer.h"
#include "OgreOverlay.h"

namespace ZS {
	class MusicUIManager {
	private:
		Ogre::v1::OverlayContainer* uiScanline;
		std::vector<Ogre::v1::OverlayContainer*> uiNotesVec;

	public:
		MusicUIManager();
		~MusicUIManager();


		Ogre::v1::Overlay* createMusicUI();



	};
}

#endif
