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

		Enemy(const std::string& name, Vec3 pos, Ogre::Quaternion rot, float hp, float maxhp, float sp, float maxsp, float str, float def, float spd, Status status, float progress, int exp);
		Enemy(const std::string& name, Vec3 pos, Ogre::Quaternion rot, Stats stats, float progress, int exp);

		void skill();
		HitInfo attack(Unit* target) override;
		Vec3 moveBack(float _distance) override;

		void update(float timeSinceLast) override;
	};

	typedef std::vector<Enemy*> EnemyVec;
}

#endif //_ENEMY_H
