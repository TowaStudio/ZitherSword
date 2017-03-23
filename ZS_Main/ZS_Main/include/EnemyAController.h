#ifndef _ZS_ENEMYACONTROLLER_H
#define _ZS_ENEMYACONTROLLER_H
#include "CharacterController.h"
#include "Enemy.h"

namespace ZS {
	class EnemyAController : public CharacterController {
	private:
		Enemy* enemy;

	public:
		EnemyAController(GameEntity* _entEnemy);
		~EnemyAController();

		virtual void changeState(ControlState _cst);

	};

}

#endif
