
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
#include <OgreTimer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlay.h>

namespace ZS
{
	extern const double FRAME_TIME;

    ZSGraphicsGameState::ZSGraphicsGameState() :
        DebugGameState(),
		gm(GameMaster::GetInstance())
    {
        
    }
    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::createScene01(void)
    {
		Ogre::SceneManager* sceneManager = mGraphicsSystem->getSceneManager();

		Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane("Plane v1",
																						  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
																						  Ogre::Plane(Ogre::Vector3::UNIT_Y, 1.0f), 50.0f, 50.0f,
																						  1, 1, true, 1, 4.0f, 4.0f, Ogre::Vector3::UNIT_Z,
																						  Ogre::v1::HardwareBuffer::HBU_STATIC,
																						  Ogre::v1::HardwareBuffer::HBU_STATIC);

		Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createManual(
			"Plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		planeMesh->importV1(planeMeshV1.get(), true, true, true);

		{
			Ogre::Item *item = sceneManager->createItem(planeMesh, Ogre::SCENE_DYNAMIC);
			item->setDatablock("Marble");
			Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->
				createChildSceneNode(Ogre::SCENE_DYNAMIC);
			sceneNode->setPosition(0, -1, 0);
			sceneNode->attachObject(item);

			//Change the addressing mode of the roughness map to wrap via code.
			//Detail maps default to wrap, but the rest to clamp.
			assert(dynamic_cast<Ogre::HlmsPbsDatablock*>(item->getSubItem(0)->getDatablock()));
			Ogre::HlmsPbsDatablock *datablock = static_cast<Ogre::HlmsPbsDatablock*>(
				item->getSubItem(0)->getDatablock());
			//Make a hard copy of the sampler block
			Ogre::HlmsSamplerblock samplerblock(*datablock->getSamplerblock(Ogre::PBSM_ROUGHNESS));
			samplerblock.mU = Ogre::TAM_WRAP;
			samplerblock.mV = Ogre::TAM_WRAP;
			samplerblock.mW = Ogre::TAM_WRAP;
			//Set the new samplerblock. The Hlms system will
			//automatically create the API block if necessary
			datablock->setSamplerblock(Ogre::PBSM_ROUGHNESS, samplerblock);
		}

		Ogre::SceneNode *rootNode = sceneManager->getRootSceneNode();

		Ogre::Light *light = sceneManager->createLight();
		Ogre::SceneNode *lightNode = rootNode->createChildSceneNode();
		lightNode->attachObject(light);
		light->setPowerScale(1.0f);
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

		mLightNodes[0] = lightNode;

		sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
									  Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
									  -light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);

		light = sceneManager->createLight();
		lightNode = rootNode->createChildSceneNode();
		lightNode->attachObject(light);
		light->setDiffuseColour(0.8f, 0.4f, 0.2f); //Warm
		light->setSpecularColour(0.8f, 0.4f, 0.2f);
		light->setPowerScale(Ogre::Math::PI);
		light->setType(Ogre::Light::LT_SPOTLIGHT);
		lightNode->setPosition(-10.0f, 10.0f, 10.0f);
		light->setDirection(Ogre::Vector3(1, -1, -1).normalisedCopy());
		light->setAttenuationBasedOnRadius(10.0f, 0.01f);

		mLightNodes[1] = lightNode;

		light = sceneManager->createLight();
		lightNode = rootNode->createChildSceneNode();
		lightNode->attachObject(light);
		light->setDiffuseColour(0.2f, 0.4f, 0.8f); //Cold
		light->setSpecularColour(0.2f, 0.4f, 0.8f);
		light->setPowerScale(Ogre::Math::PI);
		light->setType(Ogre::Light::LT_SPOTLIGHT);
		lightNode->setPosition(10.0f, 10.0f, -10.0f);
		light->setDirection(Ogre::Vector3(-1, -1, 1).normalisedCopy());
		light->setAttenuationBasedOnRadius(10.0f, 0.01f);

		mLightNodes[2] = lightNode;

		mCameraController = new CameraController(mGraphicsSystem, false);
		//createShadowMapDebugOverlays();

		DebugGameState::createScene01();
    }
    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::update( float timeSinceLast )
    {
		float weight = mGraphicsSystem->getAccumTimeSinceLastLogicFrame() / FRAME_TIME;
		weight = std::min(1.0f, weight);

		mGraphicsSystem->updateGameEntities(mGraphicsSystem->getGameEntities(Ogre::SCENE_DYNAMIC),
											weight);

		DebugGameState::update( timeSinceLast );
    }
    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::showFPS( float timeSinceLast, Ogre::String &outText )
    {
		DebugGameState::showFPS( timeSinceLast, outText );
    }
    //-----------------------------------------------------------------------------------
    void ZSGraphicsGameState::keyReleased( const SDL_KeyboardEvent &arg )
    {
		if(arg.keysym.sym == SDLK_ESCAPE) {
			mGraphicsSystem->setQuit();
		}

		DebugGameState::keyReleased(arg);
    }
}
