#include "ZSGraphicsSystem.h"

namespace ZS {

	Ogre::CompositorWorkspace* ZSGraphicsSystem::setupCompositor() {
		Ogre::CompositorManager2* compositorManager = mRoot->getCompositorManager2();
		return compositorManager->addWorkspace(mSceneManager, mRenderWindow, mCamera,
		                                       "ZSWorkspace", true);
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
