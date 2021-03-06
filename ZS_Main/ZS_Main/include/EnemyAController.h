﻿#ifndef _ZS_ENEMYACONTROLLER_H
#define _ZS_ENEMYACONTROLLER_H
#include "CharacterController.h"
#include "Enemy.h"

namespace ZS {
	class EnemyAController : public CharacterController {
	private:
		Enemy* enemy;

		enum AIState {
			AIST_IDLE = 0,
			AIST_RUN, 
			AIST_ATTACK, 
			AIST_REST1
		};

		AIState aist;

		float distance; // distance to the player
		const float runawayThres = 20.0f; // run out of attack range
		const float runThres = 10.0f; // thres to stop run
		const float detectThres = 100.0f; // thres to detect player

		void changeAstTo(ControlState _ast) override;
		float getDistanceToPlayer();

	public:
		EnemyAController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id);
		~EnemyAController();

		void changeActionState() override; // called in update

		void changeAIState() override;

	};

}

#endif
