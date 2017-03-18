#ifndef _ZS_SWORDSMANCONTROLLER_H
#define _ZS_SWORDSMANCONTROLLER_H

#include "CharacterController.h"
#include "Swordsman.h"

namespace ZS {
	class SwordsmanController : public CharacterController {
	private:
		Swordsman* swordsman;
	public:
		SwordsmanController(GameEntity* _entSwordsman, PathFollowHelper* _pafh);
		~SwordsmanController();

		virtual void changeState(ControlState _cst);
	};
}

#endif
