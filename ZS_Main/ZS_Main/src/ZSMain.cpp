#include "ZSGraphicsSystem.h"
#include "ZSGraphicsGameState.h"
#include "ZSLogicSystem.h"
#include "ZSLogicGameState.h"

#include "OgreSceneManager.h"

//Declares WinMain / main
#include "MainEntryPointHelper.h"
#include "System/MainEntryPoints.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMainApp( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow )
#else
int mainApp( int argc, const char *argv[] )
#endif
{
	// The main entry point of the application <MainEntryPoints.cpp, MainLoopMultiThreaded.cpp>
    return ZS::MainEntryPoints::mainAppMultiThreaded( MAIN_ENTRY_PARAMS );
}

namespace ZS
{
    void MainEntryPoints::createSystems( GameState **outGraphicsGameState,
                                         GraphicsSystem **outGraphicsSystem,
                                         GameState **outLogicGameState,
                                         LogicSystem **outLogicSystem )
    {
        ZSGraphicsGameState *zsGrahicsGameState = new ZSGraphicsGameState("Debug Information:\n");
		ZSGraphicsSystem *zsGraphicsSystem = new ZSGraphicsSystem(zsGrahicsGameState);
    	ZSLogicGameState *zsLogicGameState = new ZSLogicGameState();
		LogicSystem *logicSystem = new LogicSystem(zsLogicGameState);

		zsLogicGameState->_notifyLogicSystem(logicSystem);
		zsGrahicsGameState->_notifyGraphicsSystem(zsGraphicsSystem);

        *outGraphicsGameState = zsGrahicsGameState;
        *outGraphicsSystem = zsGraphicsSystem;
		*outLogicGameState = zsLogicGameState;
		*outLogicSystem = logicSystem;
    }

    void MainEntryPoints::destroySystems( GameState *graphicsGameState,
                                          GraphicsSystem *graphicsSystem,
                                          GameState *logicGameState,
                                          LogicSystem *logicSystem )
    {
        delete graphicsSystem;
        delete graphicsGameState;
		delete logicSystem;
		delete logicGameState;
    }

    const char* MainEntryPoints::getWindowTitle(void)
    {
        return "ZitherSword";
    }
}
