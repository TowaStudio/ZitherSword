/**
 * Project ZS
 */

#ifndef _ZS_INPUTMANAGER_H
#define _ZS_INPUTMANAGER_H

#include "SDL_keycode.h"
#include "Instruction.h"

namespace ZS {
	class InputManager {

	public:
		InputManager() {}
		void keydown(SDL_Keycode key);
		void keyup(SDL_Keycode key);

		void registerKeyDownInstruction(SDL_Keycode _key, Instruction* _inst);
		void deregisterKeyDownInstruction(SDL_Keycode _key, Instruction* _inst);
	};
}

#endif //_INPUTMANAGER_H