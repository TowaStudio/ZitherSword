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
				AudioSystem::GetInstance()->input(NoteName::DO);
				break;
			case SDLK_j:
				AudioSystem::GetInstance()->input(NoteName::RE);
				break;
			case SDLK_k:
				AudioSystem::GetInstance()->input(NoteName::MI);
				break;
			case SDLK_l:
				AudioSystem::GetInstance()->input(NoteName::SO);
				break;
			case SDLK_SEMICOLON:
				AudioSystem::GetInstance()->input(NoteName::LA);
				break;
			default:
				break;
		}
	}

	void InputManager::keyup(SDL_Keycode key) {
		switch(key) {
			//_DEBUG_
			case SDLK_1:
				GameMaster::GetInstance()->load();
				GameMaster::GetInstance()->loadLevel(1);
				break;
			case SDLK_2:
				AudioSystem::GetInstance()->stopMusic(true);
				break;
			case SDLK_3:
				AudioSystem::GetInstance()->stopMusic(false);
				break;
			case SDLK_4:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_RUN);
				break;
			case SDLK_5:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_ATTACK);
				break;
			case SDLK_6:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_DEAD);
				break;
			case SDLK_7:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_DEFENSE);
				break;
			case SDLK_8:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_DODGE);
				break;
			case SDLK_9:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_SKILL);
				break;
			case SDLK_0:
				GameMaster::GetInstance()->getLevelManager()->ccSwordsman->changeControlState(CST_IDLE);
				break;
			//_DEBUG_
			default:
				break;
		}
	}
}
