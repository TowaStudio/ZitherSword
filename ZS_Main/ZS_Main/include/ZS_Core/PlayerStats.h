/**
* Project ZS
*/

#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "Stats.h"

namespace ZS {
	struct  PlayerStats : Stats {
	public:
		int level;
		int exp;
		//
		PlayerStats() : Stats() {
			level = 0;
			exp = 0;
		}
		PlayerStats(int _level, int _exp, float _hp, float _maxhp, float _sp, float _maxsp
					, float _str, float _def, float _spd, Status _status) : 
			Stats(_hp, _maxhp, _sp, _maxsp, _str, _def, _spd, _status)
			, level(_level)
			, exp(_exp) {
			
		}

	};
}

#endif //_PLAYERSTATS_H
