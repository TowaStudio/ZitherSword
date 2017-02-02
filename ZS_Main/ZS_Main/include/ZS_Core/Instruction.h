/**
* Project ZS
*/


#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

namespace ZS {
	class Instruction {
	public:
		Instruction();
		virtual ~Instruction() {}
		virtual void execute() = 0;
	};
}

#endif
