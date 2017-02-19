/**
* Project ZS
*/

#ifndef _ZS_STATS_H
#define _ZS_STATS_H

namespace ZS {
	enum Status {
		Normal = 0x0
	};

	struct Stats {
	public:
		float hp, maxhp;
		float sp, maxsp;
		float str, def, spd;
		Status status;

		Stats() {
			hp = maxhp = 0.0f;
			sp = maxsp = 0.0f;
			str = def = spd = 0.0f;
			status = Status::Normal;
		}
		Stats(float _hp, float _maxhp, float _sp, float _maxsp
			, float _str, float _def, float _spd, Status _status) {
			hp = _hp; maxhp = _maxhp;
			sp = _sp; maxsp = _maxsp;
			str = _str; def = _def; spd = _spd;
			status = _status;
		}
	};
}

#endif //_STATS_H
