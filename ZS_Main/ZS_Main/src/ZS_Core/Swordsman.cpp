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
		exp(stats.exp)
	{

	}

	Swordsman::~Swordsman() {
	}

	/**
	* @return HitInfo
	*/
	HitInfo Swordsman::skill() {
		return HitInfo();
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
			
		//GameMaster::GetInstance()->log(Ogre::StringConverter::toString(this->pos.x));
	}
}
