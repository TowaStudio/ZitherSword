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
			AIST_DOUDGE,
			AIST_ATTACK1,
			AIST_ATTACK2,
			AIST_READY1, 
			AIST_READY2
		};

		AIState aist;
		int attackType;
		bool isBackward;

		float distance; // distance to the player
		const float attack1Thres = 15.0f; // thres for attack
		const float attack2Thres = 25.0f; // thres for attack
		const float runThres = 8.0f; // thres to stop run
		const float detectThres = 50.0f; // thres to detect player

		void changeAstTo(ControlState _ast) override;
		float getDistanceToPlayer();

	public:
		EnemyBossController(LevelManager* _levelManager, GameEntity* _entEnemy, int _id);
		~EnemyBossController();

		void changeActionState() override; // called in update

		void changeAIState();

	};

}

#endif

