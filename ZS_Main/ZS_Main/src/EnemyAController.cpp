#include "EnemyAController.h"

namespace ZS {

	EnemyAController::EnemyAController(GameEntity* _entEnemy):
		CharacterController(_entEnemy) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
		aist = AIST_IDLE;
	}

	EnemyAController::~EnemyAController() {
	}

	void EnemyAController::changeActionState() { // called in update

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

	void EnemyAController::changeAstTo(ControlState _ast) { // internal use

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

	void EnemyAController::changeAIState() { // called to make decision

		// get d
		d = 3;

		// change state
		switch (aist) {
			case AIST_IDLE: 
				if (d < detectThres)
					aist = AIST_RUN;
				break;
			case AIST_RUN: 
				if (d < attackThres)
					aist = AIST_REST1;
				break;
			case AIST_ATTACK: 
				aist = AIST_REST1;
				break;
			case AIST_REST1: 
				if (d > attackThres)
					aist = AIST_RUN;
				else
					aist = AIST_ATTACK;
				break;
			default: 
				break;
		}

		// change control
		switch (aist) {
		case AIST_IDLE:
			changeControlState(CST_IDLE);
			break;
		case AIST_RUN:
			changeControlState(CST_RUN);
			break;
		case AIST_ATTACK:
			changeControlState(CST_ATTACK);
			break;
		case AIST_REST1:
			changeControlState(CST_IDLE);
			break;
		default:
			break;
		}
	}
}
