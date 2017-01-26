/**
 * Project ZS
 */


#ifndef _WEAPON_H
#define _WEAPON_H

#include "Item.h"

namespace ZS {
	class Weapon : public Item {
	public:
		float atk;
		float rate;
		float range;
	};
}

#endif //_WEAPON_H