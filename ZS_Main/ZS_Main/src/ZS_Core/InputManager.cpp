/**
 * Project ZS
 */

#include "InputManager.h"
#include "AudioSystem.h"
#include "GameMaster.h"
#include "EnemyAController.h"

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
			/*case SDLK_d:
				AudioSystem::GetInstance()->input(NoteName::DO);
				break;
			case SDLK_f:
				AudioSystem::GetInstance()->input(NoteName::RE);
				break;
			case SDLK_SPACE:
				AudioSystem::GetInstance()->input(NoteName::MI);
				break;
			case SDLK_j:
				AudioSystem::GetInstance()->input(NoteName::SO);
				break;
			case SDLK_k:
				AudioSystem::GetInstance()->input(NoteName::LA);
				break;*/
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
				GameMaster::GetInstance()->getLevelManager()->UnloadLevel();
				break;
			case SDLK_3:
				GameMaster::GetInstance()->loadLevel(2);
				break;
			case SDLK_4:
				GameMaster::GetInstance()->getGameUIManager()->updateHPFill(0.5f);
				break;
			/*
			case SDLK_h:
				reinterpret_cast<EnemyAController*>(GameMaster::GetInstance()->getLevelManager()->characterControllers[0])->changeAIState();
				break;
			*/
			//_DEBUG_
			default:
				break;
		}
	}

	void InputManager::setInstruction(ControlState cst) {
		LevelManager* levelManager = GameMaster::GetInstance()->getLevelManager();
		levelManager->showResult(cst);
		levelManager->ccSwordsman->changeControlState(cst);
		for(auto itr = levelManager->characterControllers.begin(); itr != levelManager->characterControllers.end(); ++itr) {
			reinterpret_cast<EnemyAController*>(*itr)->changeAIState();
		}
	}
}
