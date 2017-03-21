#include "SwordsmanController.h"

namespace ZS {

	SwordsmanController::SwordsmanController(GameEntity* _entSwordsman) :
		CharacterController(_entSwordsman) {
		swordsman = dynamic_cast<Swordsman*>(_entSwordsman->behaviour);
	}

	SwordsmanController::~SwordsmanController() {
	}

	void SwordsmanController::changeState(ControlState _cst) {
		cst = _cst;

		//_DEBUG_
		// Animation names
		//WALK walk_0
		//RUN swordRun_1
		//ATTACK attack1_2
		//SKILL attack2_3
		//BLOCK block_4
		//DODGE dodge_5
		//IDLE swordIdle_6
		//DEAD dead_7

		switch(cst) {
			case CST_IDLE:
				swordsman->spd = 0.0f;
				ent->animationController->startAnimation("swordIdle_6");
				break;
			case CST_WALK:
				ent->animationController->startAnimation("walk_0");
				break;
			case CST_RUN:
				swordsman->spd = 3.0f;
				ent->animationController->startAnimation("swordRun_1");
				break;
			case CST_ATTACK:
				swordsman->spd = 0.0f;
				ent->animationController->startAnimation("attack1_2");
				break;
			case CST_SKILL:
				ent->animationController->startAnimation("attack2_3");
				break;
			case CST_DEFENSE:
				ent->animationController->startAnimation("block_4");
				break;
			case CST_DODGE:
				ent->animationController->startAnimation("dodge_5");
				break;
			case CST_DEAD:
				ent->animationController->startAnimation("dead_7");
				break;
			default:
				break;
		}
	}
}
