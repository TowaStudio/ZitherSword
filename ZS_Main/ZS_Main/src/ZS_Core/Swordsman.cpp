/**
 * Project ZS
 */


#include "Swordsman.h"
#include "GameMaster.h"
#include "LevelManager.h"


namespace ZS {

	/**
	* Swordsman implementation
	*/
	Swordsman::Swordsman(PlayerStats stats, Vec3 startPos, Ogre::Quaternion startRotation, float startProgress) :
		Unit("Swordsman", Tag::PLAYER, startPos, startRotation, GameMaster::GetInstance()->getLevelManager()->getUnitID()
			 , stats.hp, stats.maxhp
			 , stats.sp, stats.maxsp
			 , stats.str, stats.def, stats.spd, stats.status, startProgress),
		level(stats.level),
		exp(stats.exp),
		reachEnd(false)
	{

	}

	Swordsman::~Swordsman() {
	}

	/**
	* @return HitInfo
	*/
	void Swordsman::skill() {
		vector<Unit*> enemies = gm->getLevelManager()->unitVec;
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i] == nullptr) continue;
			float distance = (enemies[i]->progress - this->progress) * path->totalLength;
			if (distance <= (weapon == nullptr ? 1.0f : weapon->range * 2)) { // 2 times of range
				HitInfo hit;
				hit.source = this;
				hit.target = enemies[i];
				hit.dmg = Unit::CalculateDamage(this, enemies[i]) * 4; // 4 times of dmg
				hit.isCritical = false; // TODO: random critical
				hit.isFatal = hit.dmg >= enemies[i]->hp;
				hit.valid = false;

				hit.target->damage(hit.dmg);
				gm->getLevelManager()->addHitInfo(hit);
			}
		}
	}

	Vec3 Swordsman::move(float _scale) {
		if(!isDead) {
			if(path) {
				float step = _scale * spd / path->totalLength;
				float nextProgress = std::min(std::max(progress + step, 0.0f), 1.0f);
				
				// Trigger event for the path point
				int nextPathPointIndex = path->getIndexFromPos(nextProgress);
				if(currentPathPointIndex != nextPathPointIndex) {
					if(path->getPoint(nextPathPointIndex)->hasTrigger) {
						path->getPoint(nextPathPointIndex)->trigger->execute();
					}
					
					currentPathPointIndex = nextPathPointIndex;
				}
				// Prevent from going outside
				progress = nextProgress;

				moveVec = path->getPosInPath(progress) - pos;
				Ogre::Quaternion q;
				q.FromAngleAxis(Ogre::Math::ATan2(-moveVec.z, moveVec.x) - Ogre::Radian(Ogre::Math::PI / 2.0f), Vec3::UNIT_Y);
				rot = q;
			}
			pos += moveVec;
		}
		return pos;
	}

	Vec3 Swordsman::moveBack(float _distance) {
		if (!isDead) {
			if (path) {
				float step = _distance / path->totalLength;
				float nextProgress = std::min(std::max(progress - step, 0.0f), 1.0f);
				progress = nextProgress;
				moveTo(path->getPosInPath(nextProgress));
			}
		}
		return pos;
	}
	
	HitInfo Swordsman::attack(Unit* target) {
		return Unit::attack(target);
	}

	void Swordsman::heal(float amount) {
		//TODO: Add scene out
		Unit::heal(amount);
	}

	void Swordsman::update(float timeSinceLast) {
		if(isMoving) {
			move(timeSinceLast);
		}
			
		if(isAttacking) {
			if(attackTimer < 0.0f) {
				Unit* enemy = gm->getLevelManager()->getClosestEnemy(progress, weapon == nullptr ? 0.5f : weapon->range);
				attack(enemy);
			}
				
			else
				attackTimer -= timeSinceLast;
		}			
		
		if(progress >= 0.95f) {
			reachEnd = true;
		}
	}
}
