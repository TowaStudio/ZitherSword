﻿#include "EnemyAController.h"

namespace ZS {

	EnemyAController::EnemyAController(GameEntity* _entEnemy):
		CharacterController(_entEnemy) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
	}

	EnemyAController::~EnemyAController() {
	}

	void EnemyAController::changeState(ControlState _cst) {
		cst = _cst;

		switch(cst) {
			case CST_IDLE:
				enemy->isMoving = false;
				//ent->animationController->startAnimation("swordIdle_6");
				break;
			case CST_WALK:
				//ent->animationController->startAnimation("walk_0");
				break;
			case CST_RUN:
				enemy->isMoving = true;
				//ent->animationController->startAnimation("swordRun_1");
				break;
			case CST_ATTACK:
				enemy->isMoving = false;
				//ent->animationController->startAnimation("attack1_2");
				break;
			case CST_SKILL:
				//ent->animationController->startAnimation("attack2_3");
				break;
			case CST_DEFENSE:
				//ent->animationController->startAnimation("block_4");
				break;
			case CST_DODGE:
				//ent->animationController->startAnimation("dodge_5");
				break;
			case CST_DEAD:
				//ent->animationController->startAnimation("dead_7");
				break;
			default:
				break;
		}
	}
}