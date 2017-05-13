﻿#ifndef _ZS_SWORDSMANCONTROLLER_H
#define _ZS_SWORDSMANCONTROLLER_H

#include "CharacterController.h"
#include "Swordsman.h"

namespace ZS {
	class SwordsmanController : public CharacterController {
	private:
		Swordsman* swordsman;

		bool deathEndLevelCalled = false;

		float distance; // distance to the nearest enemy
		const float attackThres = 12.0f; // thres for attack
		const float runThres = 5.0f; // thres for run
		const float skillThres = 18.0f; // thres for skill
		const float detectThres = 50.0f;

		void changeAstTo(ControlState _ast) override;
		float getDistanceToClosestEnemy();

	public:
		SwordsmanController(LevelManager* _levelManager, GameEntity* _entSwordsman, int _id);
		~SwordsmanController();

		void changeActionState() override;
	};
}

#endif
