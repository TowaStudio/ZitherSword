#include "ZSGraphicsSystem.h"

#include "Hlms/Ink/OgreHlmsInk.h"
#include "Hlms/Unlit/OgreHlmsUnlit.h"
#include "Hlms/Pbs/OgreHlmsPbs.h"
#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

namespace ZS {

	/*Ogre::CompositorWorkspace* ZSGraphicsSystem::setupCompositor() {
		Ogre::CompositorManager2* compositorManager = mRoot->getCompositorManager2();
		return compositorManager->addWorkspace(mSceneManager, mRenderWindow, mCamera,
		                                       "ZSWorkspace", true);
	}*/

	//-----------------------------------------------------------------------------------
	void ZSGraphicsSystem::registerHlms(void) {
		Ogre::ConfigFile cf;
		cf.load(mResourcePath + "resources2.cfg");

		Ogre::String dataFolder = mResourcePath + cf.getSetting("DoNotUseAsResource", "Hlms", "");

		if(dataFolder.empty())
			dataFolder = "./";
		else if(*(dataFolder.end() - 1) != '/')
			dataFolder += "/";

		Ogre::RenderSystem *renderSystem = mRoot->getRenderSystem();

		Ogre::String shaderSyntax = "GLSL";
		if(renderSystem->getName() == "Direct3D11 Rendering Subsystem")
			shaderSyntax = "HLSL";
		else if(renderSystem->getName() == "Metal Rendering Subsystem")
			shaderSyntax = "Metal";

		Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Common/" + shaderSyntax,
			"FileSystem", true);
		Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Common/Any",
			"FileSystem", true);

		Ogre::ArchiveVec library;
		library.push_back(archiveLibrary);
		library.push_back(archiveLibraryAny);

		Ogre::Archive *archiveInk = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Ink/" + shaderSyntax,
			"FileSystem", true);

		Ogre::HlmsInk *hlmsInk = OGRE_NEW Ogre::HlmsInk(archiveInk, &library);
		Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsInk);

		Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Unlit/" + shaderSyntax,
			"FileSystem", true);

		Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
		Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);

		Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(
			dataFolder + "Hlms/Pbs/" + shaderSyntax,
			"FileSystem", true);
		Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &library);
		Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);

		if(renderSystem->getName() == "Direct3D11 Rendering Subsystem") {
			//Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
			//and below to avoid saturating AMD's discard limit (8MB) or
			//saturate the PCIE bus in some low end machines.
			bool supportsNoOverwriteOnTextureBuffers;
			renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV",
											 &supportsNoOverwriteOnTextureBuffers);

			if(!supportsNoOverwriteOnTextureBuffers) {
				hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
				hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
				hlmsInk->setTextureBufferDefaultSize(512 * 1024);
			}
		}
	}

	void ZSGraphicsSystem::setupResources() {
		GraphicsSystem::setupResources();

		Ogre::ConfigFile cf;
		cf.load(mResourcePath + "resources2.cfg");

		Ogre::String originalDataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

		if (originalDataFolder.empty()) originalDataFolder = "./";
		else if (*(originalDataFolder.end() - 1) != '/') originalDataFolder += "/";

		const char* c_locations[9] =
		{
			"2.0/scripts/materials/Common",
			"2.0/scripts/materials/Common/GLSL",
			"2.0/scripts/materials/Common/HLSL",
			"2.0/scripts/materials/Common/Metal",
			"2.0/scripts/materials/HDR",
			"2.0/scripts/materials/HDR/GLSL",
			"2.0/scripts/materials/HDR/HLSL",
			"2.0/scripts/materials/HDR/Metal",
			"2.0/scripts/materials/PbsMaterials"
		};

		for (size_t i = 0; i < 9; ++i) {
			Ogre::String dataFolder = originalDataFolder + c_locations[i];
			addResourceLocation(dataFolder, "FileSystem", "General");
		}
	}

	ZSGraphicsSystem::ZSGraphicsSystem(GameState* gameState):
		GraphicsSystem(gameState) {
	}
}
