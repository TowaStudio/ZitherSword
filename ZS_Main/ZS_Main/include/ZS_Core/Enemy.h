/**
 * Project ZS
 */


#ifndef _ZS_ENEMY_H
#define _ZS_ENEMY_H

#include "Unit.h"
#include "Stats.h"

namespace ZS {
	class Enemy : public Unit {
	public:
		int exp;

		Enemy(const std::string& name, Vec3 pos, float hp, float maxhp, float sp, float maxsp, float str, float def, float spd, Status status, int exp);
		Enemy(const std::string& name, Vec3 pos, Stats stats, int exp);

		HitInfo attack() override;

		void update(float timeSinceLast) override;
	};

	typedef std::vector<Enemy> EnemyVec;
}

#endif //_ENEMY_H
