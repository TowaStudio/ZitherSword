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
		Unit(const std::string& _name, Tag _tag, Vec3 _pos, Ogre::Quaternion _rot, int _id, float _hp, float _maxhp, float _sp, float _maxsp, float _str, float _def, float _spd, Status _status, float _progress, Vec3 _moveVec = Vec3::ZERO);
		Unit(const std::string& _name, Tag _tag, Vec3 _pos, Ogre::Quaternion _rot, int _id, Stats _stats, float _progress, Vec3 _moveVec = Vec3::ZERO);
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

		bool isDead;

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
		virtual Vec3 move(float _scale = 1.0f);
		Vec3 move(Vec3 _movement);
		Vec3 moveTo(Vec3 _pos);
		virtual Vec3 moveBack(float _distance = 2.0f);
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
