#ifndef _ZS_GENERATEENEMYEVENT_H
#define _ZS_GENERATEENEMYEVENT_H

#include "Event.h"
#include "Enemy.h"

namespace ZS {
	class GenerateEnemyEvent : public Event {
	private:
		Vec3 pos;
		EnemyVec enemyVec;

	public:
		GenerateEnemyEvent(Vec3 _pos);
		virtual ~GenerateEnemyEvent();

		void addEnemy(Enemy* enemy);

		virtual void execute();
	};
}

#endif
