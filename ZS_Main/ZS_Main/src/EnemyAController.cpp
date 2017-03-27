#include "EnemyAController.h"
#include "GameMaster.h"

namespace ZS {

	EnemyAController::EnemyAController(GameEntity* _entEnemy, int _id) :
		CharacterController(_entEnemy, _id), distance(0) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
		aist = AIST_IDLE;
	}

	EnemyAController::~EnemyAController() {
	}

	float EnemyAController::getDistanceToPlayer() {
		distance = enemy->progress - GameMaster::GetInstance()->getLevelManager()->getSwordsman()->progress;
		distance *= GameMaster::GetInstance()->getLevelManager()->getLevelPath()->totalLength;
		return distance;
	}

	void EnemyAController::changeActionState() { // called in update

		// get d
		getDistanceToPlayer();

		switch(cst) {
			case CST_IDLE:
				changeAstTo(cst);
				break;
			case CST_WALK:
				if (distance > runThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_IDLE);
				break;
			case CST_RUN:
				if (distance > runThres)
					changeAstTo(cst);
				else 
					changeAstTo(CST_IDLE);
				break;
			case CST_ATTACK:
				if (distance < attackThres)
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
			ent->animationController->startAnimation("swordIdle_6");
			break;
		case CST_WALK:
			ent->animationController->startAnimation("walk_0");
			break;
		case CST_RUN:
			enemy->isMoving = true;
			ent->animationController->startAnimation("swordRun_1");
			break;
		case CST_ATTACK:
			enemy->isMoving = false;
			ent->animationController->startAnimation("enemyAtk2_3");
			break;
		case CST_SKILL:
			ent->animationController->startAnimation("enemyAtk1_2");
			break;
		case CST_DEFENSE:
			ent->animationController->startAnimation("Block");
			break;
		case CST_HURT:
			ent->animationController->startAnimation("hurt_4");
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

	void EnemyAController::changeAIState() { // called to make decision

		// get d
		getDistanceToPlayer();

		// change state
		switch (aist) {
			case AIST_IDLE: 
				if (distance < detectThres)
					aist = AIST_RUN;
				break;
			case AIST_RUN: 
				if (distance < attackThres)
					aist = AIST_REST1;
				break;
			case AIST_ATTACK: 
				aist = AIST_REST1;
				break;
			case AIST_REST1: 
				if (distance > attackThres)
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
