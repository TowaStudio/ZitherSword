// GameStates and systems
#include "ZSGraphicsSystem.h"
#include "ZSGraphicsGameState.h"
#include "ZSLogicSystem.h"
#include "ZSLogicGameState.h"

#include "OgreSceneManager.h"

// ZS_Core
#include "GameMaster.h"
#include "ScreenLogger.h"

// Declares WinMain / main
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
	extern const double FRAME_TIME;
	const double FRAME_TIME = 1.0 / 60.0;

    void MainEntryPoints::createSystems( GameState **outGraphicsGameState,
                                         GraphicsSystem **outGraphicsSystem,
                                         GameState **outLogicGameState,
                                         LogicSystem **outLogicSystem )
    {
		ZSGraphicsGameState *zsGrahicsGameState = new ZSGraphicsGameState();
		ZSGraphicsSystem *zsGraphicsSystem = new ZSGraphicsSystem(zsGrahicsGameState);
    	ZSLogicGameState *zsLogicGameState = new ZSLogicGameState();
		ZSLogicSystem *zsLogicSystem = new ZSLogicSystem(zsLogicGameState);

		GameMaster* gm = GameMaster::GetInstance();
		LevelManager* levelManager = new LevelManager(zsGraphicsSystem, zsLogicSystem);
		gm->bindLevelManager(levelManager);

		ScreenLogger* screenLogger = ScreenLogger::GetInstance();
		screenLogger->bindGraphicsGameState(zsGrahicsGameState);
		gm->setLogger(screenLogger);

		zsLogicGameState->_notifyLogicSystem(zsLogicSystem);
		zsGrahicsGameState->_notifyGraphicsSystem(zsGraphicsSystem);

		zsGraphicsSystem->_notifyLogicSystem(zsLogicSystem);
		zsLogicSystem->_notifyGraphicsSystem(zsGraphicsSystem);

        *outGraphicsGameState = zsGrahicsGameState;
        *outGraphicsSystem = zsGraphicsSystem;
		*outLogicGameState = zsLogicGameState;
		*outLogicSystem = zsLogicSystem;
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
