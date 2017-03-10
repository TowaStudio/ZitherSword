/**
 * Project ZS
 */


#include "Enemy.h"
#include "Swordsman.h"
#include "GameMaster.h"

namespace ZS {
	Enemy::Enemy(const std::string& name, Vec3 pos,
		float hp, float maxhp, float sp, float maxsp,
		float str, float def, float spd, Status status, int exp) : 
		Unit(name, Tag::ENEMY, pos, GameMaster::GetInstance()->getLevelManager()->getUnitID(),
			hp, maxhp, sp, maxsp, str, def, spd, status),
		exp(exp)
	{

	}

	Enemy::Enemy(const std::string& name, Vec3 pos,
		Stats stats, int exp) : 
		Unit(name, Tag::ENEMY, pos, GameMaster::GetInstance()->getLevelManager()->getUnitID(), stats),
		exp(exp)
	{

	}

	HitInfo Enemy::attack() {
		//TODO: Scene Query to test attack range.

		//DEBUG
		Swordsman* player = GameMaster::GetInstance()->getLevelManager()->GetSwordsman();
		//Calculate dmg
		float dmg = 200.0f;
		player->damage(dmg);
		HitInfo hit(this, player, dmg, Time(0));

		return hit;
	}

	void Enemy::update(float timeSinceLast) {
		GameMaster::GetInstance()->log("Enemy log gm in update");
	}
}
