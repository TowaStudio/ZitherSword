
#ifndef _ZS_LogicSystem_H_
#define _ZS_LogicSystem_H_

#include "BaseSystem.h"
#include "OgrePrerequisites.h"
#include "SdlInputHandler.h"

namespace ZS
{
    class GameEntityManager;

    class LogicSystem : public BaseSystem
    {
    protected:
        BaseSystem          *mGraphicsSystem;
        GameEntityManager   *mGameEntityManager;

        Ogre::uint32                mCurrentTransformIdx;
        std::deque<Ogre::uint32>    mAvailableTransformIdx;

		//GameMaster* gm;

        /// @see MessageQueueSystem::processIncomingMessage
        virtual void processIncomingMessage( Mq::MessageType messageId, const void *data );

    public:
        LogicSystem( GameState *gameState );
        virtual ~LogicSystem();
	    void _notifyGraphicsSystem( BaseSystem *graphicsSystem )    { mGraphicsSystem = graphicsSystem; }
        void _notifyGameEntityManager( GameEntityManager *mgr )     { mGameEntityManager = mgr; }

        void finishFrameParallel(void);

        GameEntityManager* getGameEntityManager(void)               { return mGameEntityManager; }
        Ogre::uint32 getCurrentTransformIdx(void) const             { return mCurrentTransformIdx; }
    };
}

#endif
