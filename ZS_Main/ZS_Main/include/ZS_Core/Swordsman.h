/**
 * Project ZS
 */


#ifndef _SWORDSMAN_H
#define _SWORDSMAN_H

#include "Unit.h"
#include "SaveData.h";

namespace ZS {

	class Swordsman : public Unit {
	public:
		Swordsman(PlayerStats stats);
		~Swordsman();

		int level;
		int exp;

		HitInfo* skill();
	};
}

#endif //_SWORDSMAN_H
