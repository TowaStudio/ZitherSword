
#ifndef _ZSGRAPHICSGAMESTATE_H
#define _ZSGRAPHICSGAMESTATE_H

#include "OgrePrerequisites.h"
#include "DebugGameState.h"
#include "GameMaster.h"

namespace ZS
{
	class GameMaster;

	class ZSGraphicsGameState : public DebugGameState
    {
        Ogre::SceneNode     *mSceneNode[16];
        Ogre::SceneNode     *mLightNodes[3];

        bool                mAnimateObjects;
        Ogre::uint32        mCurrentPreset;

        Ogre::String mPresetName;
        float mExposure;
        float mMinAutoExposure;
        float mMaxAutoExposure;
        float mBloomFullThreshold;

		GameMaster* gm;

        virtual void showFPS( float timeSinceLast, Ogre::String &outText );

        void switchPreset( int direction=1 );

    public:
		ZSGraphicsGameState();

	    virtual void createScene01(void);

        virtual void update( float timeSinceLast );

        virtual void keyReleased( const SDL_KeyboardEvent &arg );
    };
}

#endif
