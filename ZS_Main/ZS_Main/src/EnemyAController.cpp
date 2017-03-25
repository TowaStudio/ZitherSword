#include "EnemyAController.h"

namespace ZS {

	EnemyAController::EnemyAController(GameEntity* _entEnemy):
		CharacterController(_entEnemy) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
	}

	EnemyAController::~EnemyAController() {
	}

	void EnemyAController::changeActionState() {

		// get d
		// TODO how to get distance
		d = 3;

		switch(cst) {
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
				changeAstTo(cst);
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

	void EnemyAController::changeAstTo(ControlState _ast) {

		if (_ast == ast) return;

		ast = _ast;
		switch (ast) {
		case CST_IDLE:
			enemy->isMoving = false;
			ent->animationController->startAnimation("Idle");
			break;
		case CST_WALK:
			ent->animationController->startAnimation("Walk");
			break;
		case CST_RUN:
			enemy->isMoving = true;
			ent->animationController->startAnimation("Run");
			break;
		case CST_ATTACK:
			enemy->isMoving = false;
			ent->animationController->startAnimation("Attack1");
			break;
		case CST_SKILL:
			ent->animationController->startAnimation("Attack2");
			break;
		case CST_DEFENSE:
			ent->animationController->startAnimation("Block");
			break;
		case CST_DODGE:
			ent->animationController->startAnimation("Dodge");
			break;
		case CST_DEAD:
			ent->animationController->startAnimation("Dead");
			break;
		default:
			break;
		}
	}
}
