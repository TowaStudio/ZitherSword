#include "SwordsmanController.h"

namespace ZS {

	SwordsmanController::SwordsmanController(GameEntity* _entSwordsman) :
		CharacterController(_entSwordsman, 0) {
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
				swordsman->isMoving = false;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("swordIdle_6");
				break;
			case CST_WALK:
				swordsman->isMoving = true;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("walk_0");
				break;
			case CST_RUN:
				swordsman->isMoving = true;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("swordRun_1");
				break;
			case CST_ATTACK:
				swordsman->isMoving = false;
				swordsman->isAttacking = true;
				ent->animationController->startAnimation("attack1_2");
				break;
			case CST_SKILL:
				swordsman->isMoving = false;
				swordsman->isAttacking = true;
				ent->animationController->startAnimation("attack2_3");
				break;
			case CST_DEFENSE:
				swordsman->isMoving = false;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("block_4");
				break;
			case CST_DODGE:
				swordsman->isMoving = false;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("dodge_5");
				break;
			case CST_DEAD:
				swordsman->isMoving = false;
				swordsman->isAttacking = false;
				ent->animationController->startAnimation("dead_7");
				break;
			default:
				break;
		}
	}
}
