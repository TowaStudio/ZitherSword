
#ifndef _ZS_MqMessages_H_
#define _ZS_MqMessages_H_

#include <vector>
#include <assert.h>

namespace ZS
{
namespace Mq
{
    enum MessageType
    {
        //Graphics <-  Logic
        LOGICFRAME_FINISHED,
        GAME_ENTITY_ADDED,
        GAME_ENTITY_REMOVED,
		GAME_ENTITY_PLAY_ANIMATION,
		GAME_ENTITY_STOP_ANIMATION,
		INIT_LEVEL_START,
        //Graphics <-> Logic
        GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
        //Graphics  -> Logic
        SDL_EVENT,
		SDL_KEYDOWN,
		SDL_KEYUP,
		INIT_LEVEL_DONE,

        NUM_MESSAGE_TYPES
    };
}
}

#endif
