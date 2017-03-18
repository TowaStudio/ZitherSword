/**
* Project ZS
*/


#ifndef _ZS_INSTRUCTION_H
#define _ZS_INSTRUCTION_H

namespace ZS {
	enum INSTRUCTION {
		INST_IDLE = 0,
		INST_ATTACK,
		INST_MOVE,
		NUM_INSTRUCTION
	};

	class Instruction {
	public:
		Instruction();
		virtual ~Instruction() {}
		virtual void execute() = 0;
	};
}

#endif
