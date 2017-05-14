#include "EnemyEliteController.h"
#include "GameMaster.h"

namespace ZS {

	EnemyEliteController::EnemyEliteController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id) :
		CharacterController(_levelManager, _entEnemy, _id), distance(0) {
		enemy = dynamic_cast<Enemy*>(_entEnemy->behaviour);
		aist = AIST_IDLE;
	}

	EnemyEliteController::~EnemyEliteController() {
	}

	float EnemyEliteController::getDistanceToPlayer() {
		distance = enemy->progress - levelManager->getSwordsman()->progress;
		distance *= levelManager->getLevelPath()->totalLength;
		return distance;
	}

	void EnemyEliteController::changeActionState() { // called in update
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
				changeAstTo(CST_ATTACK);
			break;
		case CST_RUN:
			if (distance > runThres)
				changeAstTo(cst);
			else
				changeAstTo(CST_ATTACK);
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

	void EnemyEliteController::changeAstTo(ControlState _ast) { // internal use
		//Attack1
		//Attack2
		//Dead
		//Dodge
		//Hurt
		//Idle
		//Run
		//Walk


		if (_ast == ast) return;

		ast = _ast;
		switch (ast) {
		case CST_IDLE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Idle", true);
			break;
		case CST_WALK:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Walk", true);
			break;
		case CST_RUN:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Walk", true);
			break;
		case CST_ATTACK:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "Attack1", true);
			break;
		case CST_SKILL:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "Attack2", true);
			break;
		case CST_DEFENSE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Block", true);
			break;
		case CST_HURT:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Hurt", true);
			break;
		case CST_DODGE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Dodge", true);
			break;
		case CST_DEAD:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "Dead", false);
			break;
		default:
			break;
		}
	}

	void EnemyEliteController::changeAIState() { // called to make decision

		// get d
		getDistanceToPlayer();

		// change state
		switch (aist) {
		case AIST_IDLE:
			if (distance < detectThres)
				aist = AIST_WALK;
			break;
		case AIST_WALK:
			if (distance < runThres)
				aist = AIST_ATTACK;
			break;
		case AIST_ATTACK:
			if (distance > runawayThres)
				aist = AIST_WALK;
			else
				aist = AIST_REST1;
			break;
		case AIST_REST1:
			if (distance > runawayThres)
				aist = AIST_WALK;
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
		case AIST_WALK:
			changeControlState(CST_WALK);
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
