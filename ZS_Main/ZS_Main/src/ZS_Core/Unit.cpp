/**
 * Project ZS
 */

#include "Unit.h"
#include "Stats.h"
#include "GameMaster.h"

namespace ZS {
	Unit::Unit(const std::string& _name, Tag _tag, Vec3 _pos, Ogre::Quaternion _rot
			   , int _id, float _hp, float _maxhp, float _sp, float _maxsp, float _str, float _def, float _spd, Status _status, float _progress, Vec3 _moveVec) :
		GameObject(_name, _tag, _pos, _rot), id(_id)
		, hp(_hp), maxhp(_maxhp)
		, sp(_sp), maxsp(_maxsp)
		, str(_str), def(_def), spd(_spd)
		, status(_status), isDead(false), currentPathPointIndex(-1), progress(_progress)
		, path(nullptr), moveVec(_moveVec), isMoving(false)
		, weapon(nullptr), isAttacking(false), attackTimer(0.0f) {
	}

	Unit::Unit(const std::string& _name, Tag _tag, Vec3 _pos, Ogre::Quaternion _rot, int _id, Stats _stats, float _progress, Vec3 _moveVec) :
		GameObject(_name, _tag, _pos, _rot), id(_id)
		, hp(_stats.hp), maxhp(_stats.maxhp)
		, sp(_stats.sp), maxsp(_stats.maxsp)
		, str(_stats.str), def(_stats.def), spd(_stats.spd)
		, status(_stats.status), isDead(false), currentPathPointIndex(-1), progress(_progress)
		, path(nullptr), moveVec(_moveVec), isMoving(false)
		, weapon(nullptr), isAttacking(false), attackTimer(0.0f) {
	}

	Unit::~Unit() {
	}

	HitInfo Unit::attack(Unit* target) {
		//TODO: Scene Query and get enemy list;
		HitInfo hit;
		if(target != nullptr) {
			hit.source = this;
			hit.target = target;
			hit.dmg = Unit::CalculateDamage(this, target);
			hit.isCritical = false; // TODO: random critical
			hit.isFatal = hit.dmg >= target->hp;
			hit.valid = false;

			hit.target->damage(hit.dmg);
			gm->getLevelManager()->addHitInfo(hit);
		}

		attackTimer = 1.0f / (weapon == nullptr ? 0.5f : weapon->rate);
		return hit;
	}

	void Unit::bindPath(Path* _path) {
		path = _path;
	}

	// MOVEMENT
	Vec3 Unit::move(float _scale) {
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

	Vec3 Unit::move(Vec3 _movement) {
		if(!isDead)
			pos += _movement;
		return pos;
	}

	Vec3 Unit::moveTo(Vec3 _pos) {
		pos = _pos;
		return pos;
	}

	void Unit::useWeapon(Weapon* _weapon) {
		weapon = _weapon;
	}

	// BATTLE
	void Unit::heal(float amount) {
		hp += amount;
		if(hp > maxhp) {
			hp = maxhp;
		}
	}

	/**
	 * @return bool
	 */
	bool Unit::damage(float dmg) {
		hp -= dmg;
		if(hp <= 0.0f) {
			isDead = true;
			return true;
		}
		return false;
	}

	float Unit::CalculateDamage(Unit* source, Unit* target) {
		//TODO: Full damage calculation;
		float dmg = 0.0f;

		if(source->weapon == nullptr) {
			dmg = source->str - target->def;
		} else {
			dmg = source->str + source->weapon->atk - target->def;
		}
		
		// Minimal 1 damage
		dmg = std::max(1.0f, dmg);

		return dmg;
	}

	float Unit::CalculateDamage(FlyingProps* source, Unit* target) {
		//TODO: Full damage calculation (Flying props);
		float dmg = 0.0f;

		dmg = std::max(1.0f, source->atk - target->def);
		
		return dmg;
	}
}
