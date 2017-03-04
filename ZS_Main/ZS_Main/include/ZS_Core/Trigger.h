#ifndef _ZS_TRIGGER_H
#define _ZS_TRIGGER_H

#include "GameObject.h"
#include "Event.h"

namespace ZS {
	class Trigger {
	protected:
		Event* event;
	public:
		Trigger();
		~Trigger();

		Vec3 pos;
		void execute();		
	};
}

#endif
