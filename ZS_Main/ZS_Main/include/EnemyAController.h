#ifndef _ZS_ENEMYACONTROLLER_H
#define _ZS_ENEMYACONTROLLER_H
#include "CharacterController.h"
#include "Enemy.h"

namespace ZS {
	class EnemyAController : public CharacterController {
	private:
		Enemy* enemy;

		float d; // distance to the player
		const float attackThres = 5.0f; // thres for attack
		const float runThres = 1.0f; // thres for run

		void changeAstTo(ControlState _ast) override;

	public:
		EnemyAController(GameEntity* _entEnemy);
		~EnemyAController();

		void changeActionState() override;

	};

}

#endif
