#ifndef _ZS_GENERATEENEMYEVENT_H
#define _ZS_GENERATEENEMYEVENT_H

#include "Event.h"
#include "Enemy.h"

namespace ZS {
	class GenerateEnemyEvent : public Event {
	private:
		float progress; 
		EnemyVec enemyVec;

	public:
		GenerateEnemyEvent(float _progress);
		virtual ~GenerateEnemyEvent();

		void addEnemy(Enemy* enemy);

		virtual void execute();
	};
}

#endif
