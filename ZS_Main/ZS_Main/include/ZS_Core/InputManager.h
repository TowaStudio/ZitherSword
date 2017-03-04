/**
 * Project ZS
 */


#ifndef _ZS_INPUTMANAGER_H
#define _ZS_INPUTMANAGER_H

#include "SDL_keycode.h"
#include "AudioSystem.h"

class InputManager {

	//NoteInstruction(note) :Instruction

	//Q -> instruction(do)

public:
	InputManager() {};
	void keydown(SDL_Keycode key);
	void keyup(SDL_Keycode key);
};

#endif //_INPUTMANAGER_H