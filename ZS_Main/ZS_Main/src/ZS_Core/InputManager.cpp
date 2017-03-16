/**
 * Project ZS
 */

#include "InputManager.h"
#include "AudioSystem.h"
#include "GameMaster.h"

namespace ZS {
	void InputManager::keydown(SDL_Keycode key) {
		// test key down
		switch(key) {
			case SDLK_SPACE:
				AudioSystem::GetInstance()->input(NoteName::DO); break;
			case SDLK_j:
				AudioSystem::GetInstance()->input(NoteName::RE); break;
			case SDLK_k:
				AudioSystem::GetInstance()->input(NoteName::MI); break;
			case SDLK_l:
				AudioSystem::GetInstance()->input(NoteName::SO); break;
			case SDLK_SEMICOLON:
				AudioSystem::GetInstance()->input(NoteName::LA); break;
			default:
				break;
		}

	}

	void InputManager::keyup(SDL_Keycode key) {
		switch(key) {
			case SDLK_1:
				GameMaster::GetInstance()->load();
				GameMaster::GetInstance()->loadLevel(1);
				break;
			case SDLK_i:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeState(CST_RUN);
				break;
			case SDLK_o:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeState(CST_ATTACK);
				break;
			default:
				break;
		}
	}
}
