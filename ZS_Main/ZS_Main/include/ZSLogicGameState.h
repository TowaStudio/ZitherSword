#ifndef _ZS_LOGICGAMESTATE_H
#define _ZS_LOGICGAMESTATE_H

#include "OgrePrerequisites.h"
#include "Common/DebugGameState.h"
#include "GameMaster.h"

namespace ZS {
	class LogicSystem;
	struct GameEntity;
	struct MovableObjectDefinition;

	class ZSLogicGameState : public GameState {
	private:
		LogicSystem *mLogicSystem;
		GameMaster* gm;

	public:
		ZSLogicGameState();
		~ZSLogicGameState();

		void _notifyLogicSystem(LogicSystem *logicSystem) { mLogicSystem = logicSystem; }

		virtual void createScene01(void);
		virtual void update(float timeSinceLast);
		virtual void keyReleased(const SDL_KeyboardEvent& arg);
	};
}

#endif
