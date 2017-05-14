/**
 * Project ZS
 */

#include "InputManager.h"
#include "AudioSystem.h"
#include "GameMaster.h"
#include "EnemyAController.h"
#include "LevelManager.h"
#include "SwordsmanController.h"
#include "ZitherWomanController.h"

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
			case SDLK_RETURN:
				if(GameMaster::GetInstance()->getLevelManager()->levelState == LST_NOT_IN_LEVEL) {
					GameMaster::GetInstance()->load();
					GameMaster::GetInstance()->loadLevel(1);
				}
				if(GameMaster::GetInstance()->getLevelManager()->levelState == LST_END) {
					GameMaster::GetInstance()->getLevelManager()->NextLevel();
				}
				break;
			case SDLK_r:
				if(GameMaster::GetInstance()->getLevelManager()->levelState == LST_END) {
					GameMaster::GetInstance()->getLevelManager()->RetryLevel();
				}
			//_DEBUG_
			case SDLK_2:
				GameMaster::GetInstance()->getLevelManager()->UnloadLevel();
				break;
			case SDLK_3:
				AudioSystem::GetInstance()->stopMusic(false);
				break;
			case SDLK_4:
				GameMaster::GetInstance()->getLevelManager()->EndLevel(true);
				break;
			/*
			case SDLK_h:
				reinterpret_cast<EnemyAController*>(GameMaster::GetInstance()->getLevelManager()->characterControllers[0])->changeAIState();
				break;
			*/
			case SDLK_u:
				GameMaster::GetInstance()->getLevelManager()->ccZitherwoman->changeControlState(CST_IDLE);
				break;
			case SDLK_i:
				GameMaster::GetInstance()->getLevelManager()->ccZitherwoman->changeControlState(CST_ZITHER_JUMP_UP);
				break;
			case SDLK_o:
				GameMaster::GetInstance()->getLevelManager()->ccZitherwoman->changeControlState(CST_ZITHER_JUMP_DOWN);
				break;
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
