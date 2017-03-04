
#ifndef _ZS_LogicSystem_H_
#define _ZS_LogicSystem_H_

#include "BaseSystem.h"
#include "OgrePrerequisites.h"
#include "SdlInputHandler.h"

namespace ZS
{
    class LevelManager;

    class LogicSystem : public BaseSystem
    {
    protected:
        BaseSystem          *mGraphicsSystem;
        LevelManager* mLevelManager;

        Ogre::uint32                mCurrentTransformIdx;
        std::deque<Ogre::uint32>    mAvailableTransformIdx;

        /// @see MessageQueueSystem::processIncomingMessage
        virtual void processIncomingMessage( Mq::MessageType messageId, const void *data );

    public:
        LogicSystem( GameState *gameState );
        virtual ~LogicSystem();
	    void _notifyGraphicsSystem( BaseSystem *graphicsSystem )    { mGraphicsSystem = graphicsSystem; }
        void _notifyLevelManager( LevelManager* mgr )     { mLevelManager = mgr; }

        void finishFrameParallel(void);

        LevelManager* getGameEntityManager(void)               { return mLevelManager; }
        Ogre::uint32 getCurrentTransformIdx(void) const             { return mCurrentTransformIdx; }
    };
}

#endif
