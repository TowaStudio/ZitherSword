/**
 * Project ZS
 */

#include "Unit.h"
#include "Stats.h"
#include "GameMaster.h"

namespace ZS {
	Unit::Unit(const std::string& _name, Tag _tag, Vec3 _pos
		, int _id, float _hp, float _maxhp, float _sp, float _maxsp, float _str, float _def, float _spd, Status _status, float _progress, Vec3 _moveVec) :
		GameObject(_name, _tag, _pos), id(_id)
		, hp(_hp), maxhp(_maxhp)
		, sp(_sp), maxsp(_maxsp)
		, str(_str), def(_def), spd(_spd)
		, status(_status), currentPathPointIndex(-1), progress(_progress)
		, path(nullptr), moveVec(_moveVec), isMoving(false) {
	}

	Unit::Unit(const std::string& _name, Tag _tag, Vec3 _pos, int _id, Stats _stats, float _progress, Vec3 _moveVec) :
		GameObject(_name, _tag, _pos), id(_id)
		, hp(_stats.hp), maxhp(_stats.maxhp)
		, sp(_stats.sp), maxsp(_stats.maxsp)
		, str(_stats.str), def(_stats.def), spd(_stats.spd)
		, status(_stats.status), currentPathPointIndex(-1), progress(_progress)
		, path(nullptr), moveVec(_moveVec), isMoving(false) {
	}

	Unit::~Unit() {
	}

	HitInfo Unit::attack() {
		return HitInfo();
	}

	void Unit::bindPath(Path* _path) {
		path = _path;
	}

	// MOVEMENT
	Vec3 Unit::move(float _scale) {
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
		}
		pos += moveVec;
		return pos;
	}

	Vec3 Unit::move(Vec3 _movement) {
		pos += _movement;
		return pos;
	}

	Vec3 Unit::moveTo(Vec3 _pos) {
		pos = _pos;
		return pos;
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
			return true;
		}
		return false;
	}

	float Unit::DamageCalculate(Unit* source, Unit* target) {
		float dmg;
		dmg = std::max(1.0f, source->str - target->def);
		//TODO: Full damage calculation;
		return dmg;
	}

	float Unit::DamageCalculate(FlyingProps* source, Unit* target) {
		float dmg;
		dmg = std::max(1.0f, source->atk - target->def);
		//TODO: Full damage calculation (Flying props);
		return dmg;
	}
}
