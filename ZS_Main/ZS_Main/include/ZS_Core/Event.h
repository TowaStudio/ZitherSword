#ifndef _ZS_EVENT_H
#define _ZS_EVENT_H

namespace ZS {
	class Event {
	public:
		Event();
		virtual ~Event() {
		}
		virtual void execute();
	};
}

#endif
