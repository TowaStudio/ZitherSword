
#ifndef _ZSGRAPHICSGAMESTATE_H
#define _ZSGRAPHICSGAMESTATE_H

#include "OgrePrerequisites.h"
#include "BaseGameState.h"

namespace ZS
{
    class ZSGraphicsGameState : public BaseGameState
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

        virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );

        void switchPreset( int direction=1 );

    public:
        ZSGraphicsGameState( const Ogre::String &debugDescription );

        virtual void createScene01(void);

        virtual void update( float timeSinceLast );

        virtual void keyReleased( const SDL_KeyboardEvent &arg );
    };
}

#endif
