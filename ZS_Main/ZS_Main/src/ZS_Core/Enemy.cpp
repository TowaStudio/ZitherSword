/**
 * Project ZS
 */


#include "Enemy.h"
#include "Swordsman.h"
#include "GameMaster.h"

namespace ZS {
	Enemy::Enemy(const std::string& name, Vec3 pos,
		float hp, float maxhp, float sp, float maxsp,
		float str, float def, float spd, Status status, float progress, int exp) :
		Unit(name, Tag::ENEMY, pos, GameMaster::GetInstance()->getLevelManager()->getUnitID(),
			hp, maxhp, sp, maxsp, str, def, spd, status, progress),
		exp(exp)
	{

	}

	Enemy::Enemy(const std::string& name, Vec3 pos,
		Stats stats, float progress, int exp) : 
		Unit(name, Tag::ENEMY, pos, GameMaster::GetInstance()->getLevelManager()->getUnitID(), stats, progress),
		exp(exp)
	{

	}

	HitInfo Enemy::attack(Unit* target) {
		//TODO: Scene Query to test attack range.

		//DEBUG
		Swordsman* player = GameMaster::GetInstance()->getLevelManager()->getSwordsman();
		//Calculate dmg
		float dmg = 200.0f;
		player->damage(dmg);
		HitInfo hit(this, player, dmg, Time(0));

		return hit;
	}

	void Enemy::update(float timeSinceLast) {
		//GameMaster::GetInstance()->log("Enemy log gm in update");
	}
}
