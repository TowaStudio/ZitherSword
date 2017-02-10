#ifndef _ZS_GRAPHICS_SYSTEM_H
#define _ZS_GRAPHICS_SYSTEM_H

#include "GraphicsSystem.h"
#include "OgreCamera.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "Compositor/OgreCompositorManager2.h"

namespace ZS {
	class ZSGraphicsSystem : public GraphicsSystem {
		virtual Ogre::CompositorWorkspace* setupCompositor();

		virtual void setupResources(void);

	public:
		ZSGraphicsSystem(GameState* gameState);
	};
}

#endif
