#ifndef _ZS_GENERATEENEMYEVENT_H
#define _ZS_GENERATEENEMYEVENT_H

#include "Event.h"
#include "Enemy.h"
#include "GameMaster.h"

namespace ZS {
	class GenerateEnemyEvent : public Event {
	private:
		EnemyVec enemyList;

	public:
		GenerateEnemyEvent() {
			
		}
		virtual ~GenerateEnemyEvent();


		virtual void execute();
	};
}

#endif
