/**
 * Project ZS
 */


#ifndef _ZS_WEAPON_H
#define _ZS_WEAPON_H

#include "Item.h"

namespace ZS {
	class Weapon : public Item {
	public:
		float atk;
		float rate;
		float range;

		Weapon(int _id, float _atk, float _rate, float _range);
		~Weapon();
	};
}

#endif //_WEAPON_H