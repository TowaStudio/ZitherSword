#ifndef _ZS_GAMEUIMANAGER_H
#define _ZS_GAMEUIMANAGER_H
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"

namespace ZS {
	class GameUIManager {
	private:
		bool isEnabled;
		Ogre::v1::OverlayManager& overlayManager;

		Ogre::v1::Overlay* uiGame;
		Ogre::v1::OverlayContainer* uiCharacter;
		Ogre::v1::OverlayContainer* uiHPBar;
		Ogre::v1::OverlayElement* uiHPFill;
		Ogre::v1::OverlayContainer* uiCombo;
		Ogre::v1::OverlayContainer* uiGameResult;

		float targetHPFill;
		float hpFill;
		

	public:
		GameUIManager();
		~GameUIManager();

		void createGameUI();
		void showGameUI(bool _show);

		void update(float timeSinceLast);
		void updateHPFill(float _fill);
		void updateCombo(int combo);
		void showEnd(bool win);
		void hideEnd();
		void setHPFill(float _fill);


	};
}

#endif
