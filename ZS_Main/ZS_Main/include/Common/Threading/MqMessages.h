
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
        //Graphics <-> Logic
        GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
        //Graphics  -> Logic
        SDL_EVENT,
		SDL_KEYDOWN,
		SDL_KEYUP,

        NUM_MESSAGE_TYPES
    };
}
}

#endif
