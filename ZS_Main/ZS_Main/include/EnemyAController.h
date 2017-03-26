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

		float d; // distance to the player
		const float attackThres = 5.0f; // thres for attack
		const float runThres = 1.0f; // thres to stop run
		const float detectThres = 15.0f; // thres to detect player

		void changeAstTo(ControlState _ast) override;

	public:
		EnemyAController(GameEntity* _entEnemy);
		~EnemyAController();

		void changeActionState() override; // called in update

		void changeAIState();

	};

}

#endif
