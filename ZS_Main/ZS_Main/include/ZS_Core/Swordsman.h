/**
 * Project ZS
 */


#ifndef _ZS_SWORDSMAN_H
#define _ZS_SWORDSMAN_H

#include "Unit.h"
#include "SaveData.h"

namespace ZS {

	class Swordsman : public Unit {
	public:
		Swordsman(PlayerStats stats, Vec3 startPos, Ogre::Quaternion startRot, float startProgress);
		~Swordsman();

		int level;
		int exp;

		HitInfo skill();
		virtual Vec3 move(float _scale);
		virtual HitInfo attack(Unit* target) override;
		void heal(float amount) override;
		void update(float timeSinceLast);
	};
}

#endif //_SWORDSMAN_H
