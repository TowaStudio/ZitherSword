#include "SwordsmanController.h"
#include "GameMaster.h"
#include <winioctl.h>

namespace ZS {

	SwordsmanController::SwordsmanController(GameEntity* _entSwordsman) :
		CharacterController(_entSwordsman, 0), distance(0) {
		swordsman = dynamic_cast<Swordsman*>(_entSwordsman->behaviour);
	}

	SwordsmanController::~SwordsmanController() {
	}

	float SwordsmanController::getDistanceToClosestEnemy() {
		Unit* closestEnemy = GameMaster::GetInstance()->getLevelManager()->getClosestEnemy(swordsman->progress, detectThres);
		if (closestEnemy != nullptr) {
			distance = closestEnemy->progress - swordsman->progress;
			distance *= GameMaster::GetInstance()->getLevelManager()->getLevelPath()->totalLength;
		} else {
			distance = detectThres;
		}
		return distance;
	}

	void SwordsmanController::changeActionState() { // called in update
		if(swordsman->isDead)
			cst = CST_DEAD;
		//_DEBUG_
		// Animation names
		//WALK walk_0
		//RUN swordRun_1
		//ATTACK attack1_2
		//SKILL attack2_3
		//BLOCK block_4
		//DODGE dodge_5
		//IDLE swordIdle_6
		//DEAD dead_7

		// get d
		getDistanceToClosestEnemy();

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
				if (distance < attackThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_RUN);
				break;
			case CST_SKILL:
				if (distance < skillThres)
					changeAstTo(cst);
				else
					changeAstTo(CST_RUN);
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

	void SwordsmanController::changeAstTo(ControlState _ast) {
		if (_ast == ast && ent->animationController->isEnabled) return;

		ast = _ast;
		switch (ast) {
		case CST_IDLE:
			swordsman->isMoving = false;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("swordIdle_6");
			break;
		case CST_WALK:
			swordsman->isMoving = false;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("walk_0");
			break;
		case CST_RUN:
			swordsman->isMoving = true;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("swordRun_1");
			break;
		case CST_ATTACK:
			swordsman->isMoving = false;
			swordsman->isAttacking = true;
			ent->animationController->startAnimation("attack1_2");
			break;
		case CST_SKILL:
			swordsman->isMoving = false;
			swordsman->isAttacking = true;
			ent->animationController->startAnimation("attack2_3");
			break;
		case CST_DEFENSE:
			swordsman->isMoving = false;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("block_4");
			break;
		case CST_DODGE:
			swordsman->isMoving = false;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("dodge_5");
			break;
		case CST_DEAD:
			swordsman->isMoving = false;
			swordsman->isAttacking = false;
			ent->animationController->startAnimation("dead_7", false);
			break;
		default:
			break;
		}
	}
}
