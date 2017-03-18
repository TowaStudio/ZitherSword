#ifndef _ZS_MUSICUIMANAGER_H
#define _ZS_MUSICUIMANAGER_H

#include "OgreOverlayContainer.h"
#include "OgreOverlay.h"
#include "Behaviour.h"

namespace ZS {
	class MusicUIManager : public Behaviour {
	private:
		Ogre::v1::Overlay* uiMusic;
		Ogre::v1::OverlayContainer* uiBg;
		Ogre::v1::OverlayContainer* uiScanline;
		std::vector<Ogre::v1::OverlayContainer*> uiNotesVec;
		bool isEnabled;

	public:
		MusicUIManager();
		~MusicUIManager();

		void createMusicUI();
		void showMusicUI(bool _show);
		void update(float tineSinceLast);

		void scanlineLoop();
		void addNote();
		void clearNotes();

		// Scene part
		void updateNotes();
		void showResult();
		void clearResult();

	};
}

#endif
