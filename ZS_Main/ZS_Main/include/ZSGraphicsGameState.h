
#ifndef _ZS_GRAPHICSGAMESTATE_H
#define _ZS_GRAPHICSGAMESTATE_H

#include "OgrePrerequisites.h"
#include "DebugGameState.h"
#include "GameMaster.h"
#include "OgreOverlayPrerequisites.h"

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
		ZSGraphicsGameState();

	    virtual void createScene01(void);
		virtual void update( float timeSinceLast );

        virtual void keyReleased( const SDL_KeyboardEvent &arg );
    };
}

#endif
