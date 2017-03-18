#ifndef _ZS_CHARACTERCONTROLLER_H
#define _ZS_CHARACTERCONTROLLER_H
#include "GameEntity.h"
#include "PathFollowHelper.h"

namespace ZS {
	enum ControlState {
		CST_IDLE = 0,
		CST_WALK,
		CST_RUN,
		CST_ATTACK,
		CST_SKILL,
		CST_DEFENSE,
		CST_DODGE,
		CST_DEAD,
		NUM_CONTROL_STATE
	};

	class CharacterController {
	protected:
		GameEntity* ent;
		PathFollowHelper* pathFollowHelper;
		ControlState cst;

	public:
		CharacterController(GameEntity* _ent, PathFollowHelper* _pafh) :
			ent(_ent),
			pathFollowHelper(_pafh),
			cst(CST_IDLE)
		{

		}
		virtual ~CharacterController() {}

		virtual void changeState(ControlState _cst) {
			cst = _cst;
		}
	};
}

#endif
