/**
 * Project ZS
 */


#ifndef _UNIT_H
#define _UNIT_H

#include "GameObject.h"
#include "HitInfo.h"

namespace ZS {
	class Unit : public GameObject {
	public:
		Unit(string name, Ogre::Transform transform, Tag tag, int id, float hp, float maxhp, float sp, float maxsp, float str, float def, float spd);
		~Unit();

		int id;
		float hp;
		float maxhp;
		float sp;
		float maxsp;
		float str;
		float def;
		float spd;

		HitInfo* attack();

		bool damage(float dmg);

		void heal();
	};
}

#endif //_UNIT_H
