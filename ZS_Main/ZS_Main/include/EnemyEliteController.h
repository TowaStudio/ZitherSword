#ifndef _ZS_ENEMYELITECONTROLLER_H
#define _ZS_ENEMYELITECONTROLLER_H
#include "CharacterController.h"
#include "Enemy.h"

namespace ZS {
	class EnemyEliteController : public CharacterController {
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
		const float runawayThres = 17.5f; // run out of attack range
		const float runThres = 12.0f; // thres to stop run
		const float detectThres = 100.0f; // thres to detect player

		void changeAstTo(ControlState _ast) override;
		float getDistanceToPlayer();

	public:
		EnemyEliteController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id);
		~EnemyEliteController();

		void changeActionState() override; // called in update

		void changeAIState();

	};

}

#endif
