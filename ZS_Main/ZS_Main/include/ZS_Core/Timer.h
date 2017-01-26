/**
 * Project ZS
 */


#ifndef _TIMER_H
#define _TIMER_H

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