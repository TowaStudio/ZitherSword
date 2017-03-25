#include "SwordsmanController.h"

namespace ZS {

	SwordsmanController::SwordsmanController(GameEntity* _entSwordsman) :
		CharacterController(_entSwordsman) {
		swordsman = dynamic_cast<Swordsman*>(_entSwordsman->behaviour);
	}

	SwordsmanController::~SwordsmanController() {
	}

	void SwordsmanController::changeActionState() {

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

		// get d
		// TODO how to get distance
		d = 3;

		switch (cst) {
			case CST_IDLE:
				changeAstTo(cst);
				break;
			case CST_WALK:
				if (d > runThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_IDLE);
				break;
			case CST_RUN:
				if (d > runThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_IDLE);
				break;
			case CST_ATTACK:
				if (d < attackThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_RUN);
				break;
			case CST_SKILL:
				if (d < skillThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_RUN);
				break;
			case CST_DEFENSE:
				changeAstTo(cst);
				break;
			case CST_DODGE:
				changeAstTo(cst);
				break;
			case CST_DEAD:
				changeAstTo(cst);
				break;
			default:
				break;
		}
	}

	void SwordsmanController::changeAstTo(ControlState _ast) {
		if (_ast == ast) return;

		ast = _ast;
		switch (ast) {
		case CST_IDLE:
			swordsman->isMoving = false;
			ent->animationController->startAnimation("swordIdle_6");
			break;
		case CST_WALK:
			ent->animationController->startAnimation("walk_0");
			break;
		case CST_RUN:
			swordsman->isMoving = true;
			ent->animationController->startAnimation("swordRun_1");
			break;
		case CST_ATTACK:
			swordsman->isMoving = false;
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
