/**
 * Project ZS
 */


#include "InputManager.h"

/**
 * InputManager implementation
 */

void InputManager::keydown(SDL_Keycode key){
	// test key down
	switch (key) {
	case SDLK_SPACE:
		ZS::AudioSystem::GetInstance()->input(ZS::NoteName::DO); break;
	case SDLK_j:
		ZS::AudioSystem::GetInstance()->input(ZS::NoteName::RE); break;
	case SDLK_k:
		ZS::AudioSystem::GetInstance()->input(ZS::NoteName::MI); break;
	case SDLK_l:
		ZS::AudioSystem::GetInstance()->input(ZS::NoteName::SO); break;
	case SDLK_SEMICOLON:
		ZS::AudioSystem::GetInstance()->input(ZS::NoteName::LA); break;
	}

}

void InputManager::keyup(SDL_Keycode key) {

}
