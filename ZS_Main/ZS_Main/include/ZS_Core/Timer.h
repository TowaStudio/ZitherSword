/**
 * Project ZS
 */


#ifndef _ZS_TIMER_H
#define _ZS_TIMER_H

namespace ZS {
	struct Time {
		int time;

	public:
		Time(int time) {
			this->time = time;
		}
	};

	class Timer {
	public:
		Time getTime();
	};
}

#endif //_TIMER_H