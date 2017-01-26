/**
 * Project ZS
 */


#include "HitInfo.h"

namespace ZS {

	HitInfo::HitInfo() {
	}

	/**
	 * HitInfo implementation
	 */
	HitInfo::HitInfo(Unit* _source, Unit* _target, float _dmg) :
		source(_source),
		target(_target),
		dmg(_dmg),
		isCritical(false),
		isFatal(false),
		time(nullptr) {

	}

	HitInfo::~HitInfo() {
	}
}
