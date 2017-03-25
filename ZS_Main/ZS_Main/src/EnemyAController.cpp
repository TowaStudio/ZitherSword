#include "EnemyAController.h"

namespace ZS {

	EnemyAController::EnemyAController(GameEntity* _entEnemy, int _id) :
		CharacterController(_entEnemy, _id) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
	}

	EnemyAController::~EnemyAController() {
	}

	void EnemyAController::changeState(ControlState _cst) {
		cst = _cst;

		switch(cst) {
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
