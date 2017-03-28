
#include "ZSGraphicsGameState.h"
#include "Common\CameraController.h"
#include "Common\GraphicsSystem.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"

#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "OgreCamera.h"
#include "OgreRenderWindow.h"

#include "Hlms/Unlit/OgreHlmsUnlitDatablock.h"
#include "Hlms/Ink/OgreHlmsInk.h"
#include "Hlms/Ink/OgreHlmsInkDatablock.h"

#include "Hlms/Pbs/OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreRoot.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsTextureManager.h"
#include "Hlms/Pbs/OgreHlmsPbs.h"

#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorShadowNode.h"

#include "Common/Utils/HdrUtils.h"
#include <iostream>
#include "OgreTimer.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlay.h"

namespace ZS
{
	extern const double FRAME_TIME;

    ZSGraphicsGameState::ZSGraphicsGameState() :
		DebugGameState(),
		gm(GameMaster::GetInstance()),
		musicUIManager(nullptr), gameUIManager(nullptr),
		mainCameraPathController(nullptr) {

	}

    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::createScene01(void)
    {
		Ogre::SceneManager* sceneManager = mGraphicsSystem->getSceneManager();
		sceneManager->getRenderQueue()->setRenderQueueMode(10, Ogre::RenderQueue::V1_FAST);

		Ogre::SceneNode *rootNode = sceneManager->getRootSceneNode();

		Ogre::Light *light = sceneManager->createLight();
		Ogre::SceneNode *lightNode = rootNode->createChildSceneNode();
		lightNode->attachObject(light);
		light->setPowerScale(Ogre::Math::PI);
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

		mLightNodes[0] = lightNode;

		sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
									  Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
									  -light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);

		//light = sceneManager->createLight();
		//lightNode = rootNode->createChildSceneNode();
		//lightNode->attachObject(light);
		//light->setDiffuseColour(0.8f, 0.4f, 0.2f); //Warm
		//light->setSpecularColour(0.8f, 0.4f, 0.2f);
		//light->setPowerScale(Ogre::Math::PI);
		//light->setType(Ogre::Light::LT_SPOTLIGHT);
		//lightNode->setPosition(-10.0f, 10.0f, 10.0f);
		//light->setDirection(Ogre::Vector3(1, -1, -1).normalisedCopy());
		//light->setAttenuationBasedOnRadius(10.0f, 0.01f);

		//mLightNodes[1] = lightNode;

		//light = sceneManager->createLight();
		//lightNode = rootNode->createChildSceneNode();
		//lightNode->attachObject(light);
		//light->setDiffuseColour(0.2f, 0.4f, 0.8f); //Cold
		//light->setSpecularColour(0.2f, 0.4f, 0.8f);
		//light->setPowerScale(Ogre::Math::PI);
		//light->setType(Ogre::Light::LT_SPOTLIGHT);
		//lightNode->setPosition(10.0f, 10.0f, -10.0f);
		//light->setDirection(Ogre::Vector3(-1, -1, 1).normalisedCopy());
		//light->setAttenuationBasedOnRadius(10.0f, 0.01f);

		//mLightNodes[2] = lightNode;

		createMusicUI();
		createGameUI();
		//createShadowMapDebugOverlays();

		// Scene fly over controller
		//mCameraController = new CameraController(mGraphicsSystem, false);
		// Camera path following controller
		mainCameraPathController = new CameraPathController(mGraphicsSystem->getCamera());

		{
			/*Ogre::v1::BillboardSet* bill = sceneManager->createBillboardSet(2);
			bill->setRenderQueueGroup(10);
			bill->setMaterialName("SwordA", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
			Ogre::SceneNode* billScene = sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			billScene->attachObject(bill);
			Ogre::v1::Billboard* sunBillboard = bill->createBillboard(
				Ogre::Vector3(0, 1.0f, 0));
			sunBillboard->setDimensions(1.0, 1.0);*/
		}
		

		DebugGameState::createScene01();

		// test 
		AudioSystem::GetInstance()->setChannel();
    }
    //-----------------------------------------------------------------------------------
	void ZSGraphicsGameState::createMusicUI() {
		musicUIManager = new MusicUIManager();
		gm->bindMusicUIManager(musicUIManager);
		musicUIManager->createMusicUI();
		//musicUIManager->showMusicUI(true);
    }
	void ZSGraphicsGameState::createGameUI() {
		gameUIManager = new GameUIManager();
		gm->bindGameUIManager(gameUIManager);
		gameUIManager->createGameUI();
		//gameUIManager->showGameUI(true);
	}
	//-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::update( float timeSinceLast )
    {
		float weight = mGraphicsSystem->getAccumTimeSinceLastLogicFrame() / FRAME_TIME;
		weight = std::min(1.0f, weight);

		musicUIManager->update(timeSinceLast);
		mGraphicsSystem->updateGameEntities(mGraphicsSystem->getGameEntities(Ogre::SCENE_DYNAMIC),
											weight);

		if(mainCameraPathController->isEnabled) {
			mainCameraPathController->update(timeSinceLast);
		}
			

		DebugGameState::update( timeSinceLast );
    }
    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::showFPS( float timeSinceLast, Ogre::String &outText )
    {
		DebugGameState::showFPS( timeSinceLast, outText );
    }
    //-----------------------------------------------------------------------------------
	void ZSGraphicsGameState::keyPressed(const SDL_KeyboardEvent &arg) {
		switch(arg.keysym.sym) {
			case SDLK_SPACE:
				musicUIManager->addNote(NoteName::DO);
				break;
			case SDLK_j:
				musicUIManager->addNote(NoteName::RE); 
				break;
			case SDLK_k:
				musicUIManager->addNote(NoteName::MI);
				break;
			case SDLK_l:
				musicUIManager->addNote(NoteName::SO);
				break;
			case SDLK_SEMICOLON:
				musicUIManager->addNote(NoteName::LA);
				break;
			/*case SDLK_d:
				musicUIManager->addNote(NoteName::DO);
				break;
			case SDLK_f:
				musicUIManager->addNote(NoteName::RE);
				break;
			case SDLK_SPACE:
				musicUIManager->addNote(NoteName::MI);
				break;
			case SDLK_j:
				musicUIManager->addNote(NoteName::SO);
				break;
			case SDLK_k:
				musicUIManager->addNote(NoteName::LA);
				break;*/
			default:
				break;
		}

		DebugGameState::keyPressed(arg);
    }
	void ZSGraphicsGameState::keyReleased(const SDL_KeyboardEvent &arg) {
		if(arg.keysym.sym == SDLK_ESCAPE) {
			mGraphicsSystem->setQuit();
		}

		DebugGameState::keyReleased(arg);
	}
}
