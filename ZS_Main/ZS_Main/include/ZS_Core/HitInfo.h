/**
 * Project ZS
 */


#ifndef _HITINFO_H
#define _HITINFO_H

#include "Timer.h"

namespace ZS {
	class Unit;
	struct HitInfo {
	public:

		HitInfo();
		HitInfo(Unit* _source, Unit* _target, float _dmg, Time _time);
		~HitInfo();

		bool valid;
		Unit* source;
		Unit* target;
		float dmg;
		bool isCritical;
		bool isFatal;
		Time time;
	};
}

#endif //_HITINFO_H
