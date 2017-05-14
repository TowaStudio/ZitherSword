#include "ZitherWomanController.h"
#include "LevelManager.h"

namespace ZS {
	ZitherWomanController::ZitherWomanController(LevelManager* _levelManager, GameEntity* _ent, int _id) :
	CharacterController(_levelManager, _ent, _id) {

	}

	ZitherWomanController::~ZitherWomanController() {
	}

	void ZitherWomanController::changeActionState() {
		changeAstTo(cst);
	}

	void ZitherWomanController::changeAstTo(ControlState _ast) {
		//walk_0
		//run_1
		//salute_2
		//idleNothing_3
		//jump1_4
		//PlayZither_5
		//jump2_6

		if(_ast == ast) return;

		ast = _ast;
		switch(ast) {
			case CST_IDLE:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = false;
				levelManager->changeAnimationOf(ent->animationController, "idleNothing_3", true);
				break;
			case CST_WALK:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = false;
				levelManager->changeAnimationOf(ent->animationController, "walk_0", true);
				break;
			case CST_RUN:
				//swordsman->isMoving = true;
				//swordsman->isAttacking = false;
				levelManager->changeAnimationOf(ent->animationController, "run_1", true);
				break;
			case CST_SKILL:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = true;
				levelManager->changeAnimationOf(ent->animationController, "salute_2", true);
				break;
			case CST_ZITHER_PLAY:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = true;
				levelManager->changeAnimationOf(ent->animationController, "PlayZither_5", true);
				break;
			case CST_ZITHER_JUMP_UP:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = false;
				levelManager->changeAnimationOf(ent->animationController, "jump1_4", true);
				break;
			case CST_ZITHER_JUMP_DOWN:
				//swordsman->isMoving = false;
				//swordsman->isAttacking = false;
				levelManager->changeAnimationOf(ent->animationController, "jump2_6", true);
				break;
			default:
				break;
		}
	}
}
