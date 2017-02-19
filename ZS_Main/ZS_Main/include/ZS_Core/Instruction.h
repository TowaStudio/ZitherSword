/**
* Project ZS
*/


#ifndef _ZS_INSTRUCTION_H
#define _ZS_INSTRUCTION_H

namespace ZS {
	class Instruction {
	public:
		Instruction();
		virtual ~Instruction() {}
		virtual void execute() = 0;
	};
}

#endif
