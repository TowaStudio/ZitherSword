#include "EnemyBossController.h"
#include "GameMaster.h"

namespace ZS {

	EnemyBossController::EnemyBossController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id) :
		CharacterController(_levelManager, _entEnemy, _id), distance(0), attackType(0), isBackward(true) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
		aist = AIST_IDLE;
	}

	EnemyBossController::~EnemyBossController() {
	}

	float EnemyBossController::getDistanceToPlayer() {
		distance = enemy->progress - levelManager->getSwordsman()->progress;
		distance *= levelManager->getLevelPath()->totalLength;
		return distance;
	}
	// TODO
	void EnemyBossController::changeActionState() { // called in update
		if (enemy->isDead)
			cst = CST_DEAD;

		// get d
		getDistanceToPlayer();

		switch (cst) {
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
			if (distance < attack1Thres)
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
	// TODO
	void EnemyBossController::changeAstTo(ControlState _ast) { // internal use

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
	// TODO
	void EnemyBossController::changeAIState() { // called to make decision

		// get d
		getDistanceToPlayer();
		attackType = rand() % 2;

		// change state
		switch (aist) {
		case AIST_IDLE:\
			if (distance < attack1Thres)
				switch (attackType) {
					case 0: aist = AIST_READY1; break;
					case 1: aist = AIST_READY2; break;
					default: aist = AIST_READY1; break;
				}
			if (distance < detectThres)
				aist = AIST_RUN;
			break;
		case AIST_RUN:
			switch (attackType) {
			case 0: 
				if (distance < attack1Thres)
					aist = AIST_READY1;
			}
			if (distance < attack1Thres)
				aist = AIST_READY1;
			break;
		case AIST_ATTACK1:
			aist = AIST_READY1;
			break;
		case AIST_READY1:
			if (distance > attack1Thres)
				aist = AIST_RUN;
			else
				aist = AIST_ATTACK1;
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
		case AIST_ATTACK1:
			changeControlState(CST_ATTACK);
			break;
		case AIST_READY1:
			changeControlState(CST_IDLE);
			break;
		default:
			break;
		}
	}
}

