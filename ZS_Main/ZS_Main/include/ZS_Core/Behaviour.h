#ifndef _ZS_BEHAVIOUR_H
#define _ZS_BEHAVIOUR_H

namespace ZS {
	class Behaviour abstract {
	public:
		virtual ~Behaviour() {}

		virtual void update();
	};
}

#endif
