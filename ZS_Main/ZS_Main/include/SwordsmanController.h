#ifndef _ZS_SWORDSMANCONTROLLER_H
#define _ZS_SWORDSMANCONTROLLER_H

#include "CharacterController.h"
#include "Swordsman.h"

namespace ZS {
	class SwordsmanController : public CharacterController {
	private:
		Swordsman* swordsman;

		float d; // distance to the nearest enemy
		const float attackThres = 5.0f; // thres for attack
		const float runThres = 1.0f; // thres for run
		const float skillThres = 7.0f; // thres for skill

		void changeAstTo(ControlState _ast) override;

	public:
		SwordsmanController(GameEntity* _entSwordsman);
		~SwordsmanController();

		void changeActionState() override;
	};
}

#endif
