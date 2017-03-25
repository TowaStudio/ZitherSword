#include "Trigger.h"

namespace ZS {

	Trigger::Trigger() :
		eventVec(std::vector<Event*>()),
		eventCount(0)
	{
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
		if(eventCount > 0) {
			for(auto itr = eventVec.begin(); itr != eventVec.end(); ++itr) {
				(*itr)->execute();
			}
		}
	}
}
