#ifndef _ZS_ENEMYBOSSCONTROLLER_H
#define _ZS_ENEMYBOSSCONTROLLER_H
#include "CharacterController.h"
#include "Enemy.h"

namespace ZS {
	class EnemyBossController : public CharacterController {
	private:
		Enemy* enemy;

		enum AIState {
			AIST_IDLE = 0,
			AIST_RUN,
			AIST_DODGE,
			AIST_ATTACK1,
			AIST_ATTACK2,
			AIST_READY1, 
			AIST_READY2,
			AIST_REST
		};

		AIState aist;

		float distance; // distance to the player
		const float readyThres = 30.0f; // thres for ready
		const float attack1Thres = 15.0f; // thres for attack1
		const float runThres = 8.0f; // thres to stop run
		const float detectThres = 70.0f; // thres to detect player

		void changeAstTo(ControlState _ast) override;
		float getDistanceToPlayer();

		void RNG();

	public:
		EnemyBossController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id);
		~EnemyBossController();

		void changeActionState() override; // called in update

		void changeAIState() override;

	};

}

#endif

