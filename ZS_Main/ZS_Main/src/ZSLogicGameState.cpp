#include "ZSLogicGameState.h"
#include "Threading/MqMessages.h"
#include "AudioSystem.h"
#include "LevelManager.h"
#include <SDL.h>
#include "Enemy.h"
#include "Path.h"

namespace ZS {

	ZSLogicGameState::ZSLogicGameState() :
		mLogicSystem(nullptr),
		gm(GameMaster::GetInstance())
	{
		entities = new GameEntityVec();
	}

	ZSLogicGameState::~ZSLogicGameState() {
	}
	  
	void ZSLogicGameState::createScene01() {
		gm->log("Start in createScrene01");

		const Vec3 origin(0.0f, 0.0f, 0.0f);
		LevelManager* levelManager = mLogicSystem->getLevelManager();
		
		MovableObjectDefinition* moHead = new MovableObjectDefinition();
		moHead->meshName = "ogrehead_v2.mesh";
		moHead->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
		moHead->submeshMaterials.push_back("InkShader");
		moHead->moType = MoTypeItemInk;

		Enemy* enemyA = new Enemy("EnemyA", origin, 200.0f, 200.0f, 40.0f, 40.0f, 50.0f, 50.0f, 20.0f, Status::Normal, 20);

		entHead = levelManager->addGameEntity(Ogre::SCENE_DYNAMIC, moHead
											  , nullptr
											  , origin + Vec3(0.0f, 2.0f, 0.0f)
											  , Ogre::Quaternion::IDENTITY
											  , Vec3(0.1f, 0.1f, 0.1f));
				
		entities->push_back(entHead);
	}

	void ZSLogicGameState::createScene02() {

	}

	void ZSLogicGameState::update(float timeSinceLast) {
		const size_t currIdx = mLogicSystem->getCurrentTransformIdx();
		const size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		Vec3 newPos = entHead->mTransform[prevIdx]->vPos;
		newPos.x += timeSinceLast * 4.0f;
		newPos.x = fmodf(newPos.x, 10.0f);

		entHead->mTransform[currIdx]->vPos = newPos;

		for(auto itr = entities->begin(), end = entities->end(); itr != end; ++itr) {
			if((*itr)->behaviour)
				(*itr)->behaviour->update(timeSinceLast);
		}

		GameState::update(timeSinceLast);
	}
}
