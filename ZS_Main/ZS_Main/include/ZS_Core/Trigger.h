#ifndef _ZS_TRIGGER_H
#define _ZS_TRIGGER_H

#include "GameObject.h"
#include "Event.h"

namespace ZS {
	class Trigger {
	protected:
		std::vector<Event*> eventVec;
		int eventCount;

	public:
		Vec3 pos;

		Trigger();
		~Trigger();

		void addEvent(Event* _event);
		void removeEvent(int index);
		void removeAllEvents();

		void execute();
	};
}

#endif
