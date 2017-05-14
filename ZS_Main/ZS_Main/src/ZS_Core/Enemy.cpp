/**
 * Project ZS
 */


#include "Enemy.h"
#include "Swordsman.h"
#include "GameMaster.h"

namespace ZS {
	Enemy::Enemy(const std::string& name, Vec3 pos, Ogre::Quaternion rot,
				 float hp, float maxhp, float sp, float maxsp,
				 float str, float def, float spd, Status status, float progress, int exp) :
		Unit(name, Tag::ENEMY, pos, rot, GameMaster::GetInstance()->getLevelManager()->getUnitID(),
			 hp, maxhp, sp, maxsp, str, def, spd, status, progress),
		exp(exp) {

	}

	Enemy::Enemy(const std::string& name, Vec3 pos, Ogre::Quaternion rot,
				 Stats stats, float progress, int exp) :
		Unit(name, Tag::ENEMY, pos, rot, GameMaster::GetInstance()->getLevelManager()->getUnitID(), stats, progress),
		exp(exp) {

	}

	HitInfo Enemy::attack(Unit* target) {
		return Unit::attack(target);
	}

	void Enemy::skill() {
		Unit* swordsman = gm->getLevelManager()->getSwordsman();
		float distance = (this->progress - swordsman->progress) * path->totalLength;
		if (distance <= (weapon == nullptr ? 1.0f : weapon->range * 2)) { // 2 times of range
			HitInfo hit;
			hit.source = this;
			hit.target = swordsman;
			hit.dmg = Unit::CalculateDamage(this, swordsman) * 0.75; 
			hit.isCritical = false; // TODO: random critical
			hit.isFatal = hit.dmg >= swordsman->hp;
			hit.valid = false;

			hit.target->damage(hit.dmg);
			gm->getLevelManager()->addHitInfo(hit);
		}
	}

	Vec3 Enemy::moveBack(float _distance) {
		if (!isDead) {
			if (path) {
				float step = _distance / path->totalLength;
				float nextProgress = std::min(std::max(progress + step, 0.0f), 1.0f);
				progress = nextProgress;
				moveTo(path->getPosInPath(nextProgress));
			}
		}
		return pos;
	}


	void Enemy::update(float timeSinceLast) {
		//GameMaster::GetInstance()->log("Enemy log gm in update");
		if(isMoving) {
			move(timeSinceLast);
		}

		if(isAttacking) {
			if(attackTimer < 0.0f) {
				Unit* target = gm->getLevelManager()->getSwordsman();
				if ((weapon == nullptr ? 12.0f : weapon->range) >= (progress - target->progress) * path->totalLength) {
					attack(target);
				}
			}

			else
				attackTimer -= timeSinceLast;
		}

		//GameMaster::GetInstance()->log(Ogre::StringConverter::toString(this->pos.x));
	}
}
