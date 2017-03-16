#ifndef _ZS_INSTRUCTIONS_H
#define _ZS_INSTRUCTIONS_H

#include "Instruction.h"
#include "Swordsman.h"
#include "GameEntity.h"

namespace ZS {
	// Attack
	class INST_Attack : public Instruction {
	private:
		GameEntity* sourceEnt;
		Ogre::String animationName;

	public:
		INST_Attack(GameEntity* entity, Ogre::String attackAnimationName);
		~INST_Attack();

		void execute();
	};

	// Move
	class INST_Move : public Instruction {
	private:
		GameEntity* sourceEnt;
		Ogre::String animationName;

	public:
		INST_Move(GameEntity* entity, Ogre::String moveAnimationName);
		~INST_Move();

		void execute();
	};
}

#endif
