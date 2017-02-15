/**
 * Project ZS
 */


#ifndef _UNIT_H
#define _UNIT_H

#include "GameObject.h"
#include "HitInfo.h"
#include "Stats.h"
#include "FlyingProps.h"

namespace ZS {

	class Unit : public GameObject {
	public:
		Unit(const std::string& name, Tag tag, Vec3 pos, int id, float hp, float maxhp, float sp, float maxsp, float str, float def, float spd, Status status);
		Unit(const std::string& name, Tag tag, Vec3 pos, int id, Stats stats);
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

		virtual HitInfo attack();
		virtual void heal(float amount);
		bool damage(float dmg);
		

		static float DamageCalculate(Unit* source, Unit* target);
		static float DamageCalculate(FlyingProps* source, Unit* target);
	};
}

#endif //_UNIT_H
