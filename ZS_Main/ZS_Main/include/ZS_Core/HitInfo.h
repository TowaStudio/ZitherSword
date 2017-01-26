/**
 * Project ZS
 */


#ifndef _HITINFO_H
#define _HITINFO_H

#include "Timer.h"

namespace ZS {
	class Unit;
	class HitInfo {
	public:

		HitInfo();
		HitInfo(Unit* _source, Unit* _target, float _dmg);
		~HitInfo();

		Unit* source;
		Unit* target;
		float dmg;
		bool isCritical;
		bool isFatal;
		Time* time;
	};
}

#endif //_HITINFO_H
