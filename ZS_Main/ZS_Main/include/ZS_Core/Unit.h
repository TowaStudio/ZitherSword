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

		// MOVEMENT
		void bindPath(Path* _path);
		Vec3 move(float _scale = 1.0f);
		Vec3 move(Vec3 _movement);
		Vec3 moveTo(Vec3 _pos);
		// BATTLE
		virtual HitInfo attack();
		virtual void heal(float amount);
		bool damage(float dmg);
		

		static float DamageCalculate(Unit* source, Unit* target);
		static float DamageCalculate(FlyingProps* source, Unit* target);
	};
}

#endif //_UNIT_H
