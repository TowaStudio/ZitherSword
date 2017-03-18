#include "Instructions.h"

namespace ZS {
	//Instruction - Attack
	INST_Attack::INST_Attack(GameEntity* entity, Ogre::String attackAnimationName) :
		Instruction(),
		sourceEnt(entity),
		animationName(attackAnimationName)
	{

	}

	INST_Attack::~INST_Attack() {
	}

	void INST_Attack::execute() {
		//TODO: Get target

		//TODO: Calculate damage

		//TODO: Play Animation
		sourceEnt->animationController->startAnimation(animationName);
	}

	//Instruction - Move
	INST_Move::INST_Move(GameEntity* entity, Ogre::String moveAnimationName) : 
		Instruction(),
		sourceEnt(entity),
		animationName(moveAnimationName)
	{

	}

	INST_Move::~INST_Move() {
	}

	void INST_Move::execute() {
		//TODO: 
		reinterpret_cast<Unit*>(sourceEnt->behaviour)->move();

		sourceEnt->animationController->startAnimation(animationName);
	}
}
