
#ifndef _ZS_GRAPHICSGAMESTATE_H
#define _ZS_GRAPHICSGAMESTATE_H

#include "OgrePrerequisites.h"
#include "DebugGameState.h"
#include "GameMaster.h"
#include "OgreOverlayPrerequisites.h"
#include "MusicUIManager.h"
#include "GameUIManager.h"

namespace ZS
{
	class GameMaster;

	class ZSGraphicsGameState : public DebugGameState
    {
        Ogre::SceneNode     *mSceneNode[16];
        Ogre::SceneNode     *mLightNodes[3];

        GameMaster* gm;
		virtual void showFPS( float timeSinceLast, Ogre::String &outText );
		
	public:
		MusicUIManager* musicUIManager;
		GameUIManager* gameUIManager;
		
		Ogre::v1::Overlay* uiLogo;
		Ogre::v1::OverlayContainer* uiTitle;
		Ogre::v1::OverlayContainer* uiPressToStart;
		Ogre::v1::OverlayContainer* uiCommand;

		CameraPathController* mainCameraPathController;

		ZSGraphicsGameState();

	    virtual void createScene01(void);
		void createMusicUI();
		void createGameUI();
		virtual void update( float timeSinceLast );

		virtual void keyPressed(const SDL_KeyboardEvent& arg);
		virtual void keyReleased(const SDL_KeyboardEvent& arg);
		void HideLogo();
	};
}

#endif
