#include "EnemyBossController.h"
#include "GameMaster.h"

namespace ZS {

	EnemyBossController::EnemyBossController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id) :
		CharacterController(_levelManager, _entEnemy, _id), distance(0) {
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
			if (distance > attack1Thres)
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
	
	void EnemyBossController::changeAstTo(ControlState _ast) { // internal use
		//backward_5
		//bossAtk1_2
		//bossAtk2_3
		//daijipose_6
		//dead_7
		//hurt_4
		//run_1
		//walk_0


		if (_ast == ast) return;

		ast = _ast;
		switch (ast) {
		case CST_IDLE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "daijipose_6", true);
			break;
		case CST_WALK:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "walk_0", true);
			break;
		case CST_RUN:
			enemy->isMoving = true;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "run_1", true);
			break;
		case CST_ATTACK:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "bossAtk1_2", true);
			break;
		case CST_SKILL:
			enemy->isMoving = false;
			enemy->isAttacking = true;
			levelManager->changeAnimationOf(ent->animationController, "bossAtk2_3", true);
			break;
		case CST_HURT:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "hurt_4", true);
			break;
		case CST_DODGE:
			enemy->isMoving = false;
			enemy->isAttacking = false;
			levelManager->changeAnimationOf(ent->animationController, "backward_5", true);
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

		// change state
		switch (aist) {
		case AIST_IDLE:
			if (distance < readyThres)
				aist = AIST_ATTACK2;
			else
				aist = AIST_IDLE;
			break;
		case AIST_ATTACK1:
			aist = AIST_REST;
			break;
		case AIST_ATTACK2:
			aist = AIST_REST;
			break;
		case AIST_READY1:
			aist = AIST_ATTACK1;
			break;
		case AIST_READY2:
			aist = AIST_ATTACK2;
			break;
		case AIST_RUN:
			RNG();
			break;
		case AIST_DODGE: 
			RNG();
			break;
		case AIST_REST: 
			RNG();
			break;
		default:
			break;
		}

		// change control
		switch (aist) {
		case AIST_IDLE:
			GameMaster::GetInstance()->log("IDLE");
			changeControlState(CST_IDLE);
			break;
		case AIST_RUN:
			GameMaster::GetInstance()->log("RUN");
			changeControlState(CST_RUN);
			break;
		case AIST_DODGE:
			enemy->moveBack(10.0f);
			GameMaster::GetInstance()->log("DODGE");
			changeControlState(CST_DODGE);
			break;
		case AIST_ATTACK1:
			GameMaster::GetInstance()->log("ATK1");
			changeControlState(CST_ATTACK);
			break;
		case AIST_ATTACK2:
			GameMaster::GetInstance()->log("ATK2");
			changeControlState(CST_SKILL);
			break;
		case AIST_READY1:
			GameMaster::GetInstance()->log("RDY1");
			changeControlState(CST_RUN); // run to attack 1
			break;
		case AIST_READY2:
			enemy->moveBack(5.0f);
			GameMaster::GetInstance()->log("RDY2");
			changeControlState(CST_DODGE); // dodge to attack 2
			break;
		case AIST_REST:
			GameMaster::GetInstance()->log("REST");
			changeControlState(CST_IDLE);
			break;
		default:
			break;
		}
	}

	void EnemyBossController::RNG() { // internal use
		if (distance > detectThres) {
			// run rest
			switch (rand() % 2) {
				case 0: aist = AIST_RUN; break;
				case 1: aist = AIST_REST; break;
				default: break;
			}
		} else if (distance > readyThres) {
			// run rest dodge
			switch (rand() % 4) {
				case 0: aist = AIST_RUN; break;
				case 1: aist = AIST_RUN; break;
				case 2: aist = AIST_REST; break;
				case 3: aist = AIST_DODGE; break;
				default: break;
			}
		} else if (distance > runThres) {
			// ready1 ready2 rest dodge
			switch (rand() % 4) {
				case 0: aist = AIST_READY1; break;
				case 1: aist = AIST_READY2; break;
				case 2: aist = AIST_REST; break;
				case 3: aist = AIST_DODGE; break;
				default: break;
			}
		} else {
			aist = AIST_DODGE;
		}
	}

}

