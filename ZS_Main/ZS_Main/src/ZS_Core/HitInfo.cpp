/**
 * Project ZS
 */


#include "HitInfo.h"

namespace ZS {
	HitInfo::HitInfo() :
		valid(false),
		source(nullptr), target(nullptr),
		dmg(0.0f),
		isCritical(false), isFatal(false),
		time(Time(0))
	{

	}

	/**
	 * HitInfo implementation
	 */
	HitInfo::HitInfo(Unit* _source, Unit* _target, float _dmg, Time _time) :
		valid(true),
		source(_source), target(_target),
		dmg(_dmg),
		isCritical(false), isFatal(false),
		time(_time)
	{

	}

	HitInfo::~HitInfo() {
	}
}
