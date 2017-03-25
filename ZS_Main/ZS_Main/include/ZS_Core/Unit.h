/**
 * Project ZS
 */


#ifndef _ZS_UNIT_H
#define _ZS_UNIT_H

#include "GameObject.h"
#include "HitInfo.h"
#include "Stats.h"
#include "FlyingProps.h"
#include "Path.h"
#include "Weapon.h"

namespace ZS {

	class Unit : public GameObject {
	public:
		Unit(const std::string& name, Tag tag, Vec3 pos, int id, float hp, float maxhp, float sp, float maxsp, float str, float def, float spd, Status status, float progress, Vec3 moveVec = Vec3::ZERO);
		Unit(const std::string& name, Tag tag, Vec3 pos, int id, Stats stats, float progress, Vec3 moveVec = Vec3::ZERO);
		~Unit();

		int id;
		float hp;
		float maxhp;
		float sp;
		float maxsp;
		float str;
		float def;
		float spd;
		Status status;

		int currentPathPointIndex;
		float progress;
		Path* path;

		Vec3 moveVec;
		bool isMoving;

		Weapon* weapon;
		bool isAttacking;
		float attackTimer;

		// MOVEMENT
		void bindPath(Path* _path);
		Vec3 move(float _scale = 1.0f);
		Vec3 move(Vec3 _movement);
		Vec3 moveTo(Vec3 _pos);
		// BATTLE
		void useWeapon(Weapon* _weapon);

		virtual HitInfo attack(Unit* target);
		virtual void heal(float amount);
		bool damage(float dmg);
		

		static float CalculateDamage(Unit* source, Unit* target);
		static float CalculateDamage(FlyingProps* source, Unit* target);
	};
}

#endif //_UNIT_H
