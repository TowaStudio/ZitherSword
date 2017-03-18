#include "Trigger.h"

namespace ZS {

	Trigger::Trigger() :
		eventCount(0) {
	}

	Trigger::~Trigger() {
	}

	void Trigger::addEvent(Event* _event) {
		eventVec.push_back(_event);
		++eventCount;
	}

	void Trigger::removeEvent(int index) {
	}

	void Trigger::removeAllEvents() {
	}

	void Trigger::execute() {
	}
}
