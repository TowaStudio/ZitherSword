#ifndef _ZSLOGICGAMESTATE_H
#define _ZSLOGICGAMESTATE_H

#include "OgrePrerequisites.h"
#include "Common/BaseGameState.h"

namespace ZS {
	class LogicSystem;
	struct GameEntity;
	struct MovableObjectDefinition;

	class ZSLogicGameState : public GameState {
		LogicSystem         *mLogicSystem;

	public:
		ZSLogicGameState();
		~ZSLogicGameState();

		void _notifyLogicSystem(LogicSystem *logicSystem) { mLogicSystem = logicSystem; }

		virtual void createScene01(void);
		virtual void update(float timeSinceLast);
	};
}

#endif
