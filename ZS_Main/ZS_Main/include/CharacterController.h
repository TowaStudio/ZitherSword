#ifndef _ZS_CHARACTERCONTROLLER_H
#define _ZS_CHARACTERCONTROLLER_H
#include "GameEntity.h"

namespace ZS {
	class LevelManager;

	enum ControlState {
		CST_IDLE = 0,
		CST_WALK,
		CST_RUN,
		CST_ATTACK,
		CST_SKILL,
		CST_DEFENSE,
		CST_DODGE,
		CST_HURT,
		CST_DEAD,
		CST_ZITHER_JUMP_UP,
		CST_ZITHER_JUMP_DOWN,
		CST_ZITHER_PLAY,
		NUM_CONTROL_STATE
	};

	class CharacterController {
	protected:
		LevelManager* levelManager;
		GameEntity* ent;
		ControlState cst;
		ControlState ast;

	public:
		int id;

		CharacterController(LevelManager* _levelManager, GameEntity* _ent, int _id) :
			levelManager(_levelManager),
			ent(_ent),
			cst(CST_IDLE),
			ast(CST_IDLE),
			id(_id) {

		}

		virtual ~CharacterController() {}

		void changeControlState(ControlState _cst) {
			cst = _cst;
		}

		virtual void changeAIState() {
			
		}

		virtual void changeActionState() { // call in update
			ast = cst;
		}

	protected:
		virtual void changeAstTo(ControlState _ast) {
			ast = _ast;
		}
	};
}

#endif
