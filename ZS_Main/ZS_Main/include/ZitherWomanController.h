#ifndef _ZS_ZITHERWOMANCONTROLLER_H
#define _ZS_ZITEERWOMANCONTROLLER_H

#include "CharacterController.h"

namespace ZS {
	class ZitherWomanController : public CharacterController {
	public:
		ZitherWomanController(LevelManager* _levelManager, GameEntity* _ent, int _id);
		~ZitherWomanController();

		void changeActionState() override;
	protected:
		void changeAstTo(ControlState _ast) override;
	};
}

#endif
