#include "EnemyAController.h"
#include "GameMaster.h"

namespace ZS {

	EnemyAController::EnemyAController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id) :
		CharacterController(_levelManager, _entEnemy, _id), distance(0) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
		aist = AIST_IDLE;
	}

	EnemyAController::~EnemyAController() {
	}

	float EnemyAController::getDistanceToPlayer() {
		distance = enemy->progress - levelManager->getSwordsman()->progress;
		distance *= levelManager->getLevelPath()->totalLength;
		return distance;
	}

	void EnemyAController::changeActionState() { // called in update
		if(enemy->isDead)
			cst = CST_DEAD;

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
				changeAstTo(cst);
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
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "swordIdle_6", true);
			break;
		case CST_WALK:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "walk_0", true);
			break;
		case CST_RUN:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "swordRun_1", true);
			break;
		case CST_ATTACK:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "enemyAtk2_3", true);
			break;
		case CST_SKILL:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "enemyAtk1_2", true);
			break;
		case CST_DEFENSE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Block", true);
			break;
		case CST_HURT:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "hurt_4", true);
			break;
		case CST_DODGE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "dodge_5", true);
			break;
		case CST_DEAD:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "dead_7", false);
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
				if (distance < runThres)
					aist = AIST_REST1;
				break;
			case AIST_ATTACK: 
				if (distance > runawayThres)
					aist = AIST_RUN;
				else
					aist = AIST_REST1;
				break;
			case AIST_REST1: 
				if (distance > runawayThres)
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
