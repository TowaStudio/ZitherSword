
#include "GraphicsSystem.h"
#include "GameState.h"
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS
    #include "SdlInputHandler.h"
#endif
#include "GameEntity.h"

#include "OgreRoot.h"
#include "OgreException.h"
#include "OgreConfigFile.h"

#include "OgreRenderWindow.h"
#include "OgreCamera.h"
#include "OgreItem.h"
#include "Animation/OgreTagPoint.h"

#include "Hlms/Unlit/OgreHlmsUnlit.h"
#include "Hlms/Unlit/OgreHlmsUnlitDatablock.h"
#include "Hlms/Pbs/OgreHlmsPbs.h"
#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

#include "Compositor/OgreCompositorManager2.h"

#include "OgreOverlaySystem.h"

#include "OgreWindowEventUtilities.h"
#include "GameMaster.h"
#include "Animation/OgreSkeletonInstance.h"
#include "AnimationController.h"
#include "ZSGraphicsGameState.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"
#include <Hlms/Ink/OgreHlmsInk.h>

#if OGRE_USE_SDL2
    #include <SDL_syswm.h>
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    #include "OSX/macUtils.h"
    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        #include "System/iOS/iOSUtils.h"
    #endif
#endif

namespace ZS
{
	GraphicsSystem::GraphicsSystem(GameState *gameState,
								   Ogre::ColourValue backgroundColour) :
		BaseSystem(gameState),
		mLogicSystem(nullptr),
#if OGRE_USE_SDL2
		mSdlWindow(nullptr),
		mInputHandler(nullptr),
#endif
		mRoot(nullptr),
		mRenderWindow(nullptr),
		mSceneManager(nullptr),
		mCamera(nullptr),
		mWorkspace(nullptr),
		mOverlaySystem(nullptr),
		mAccumTimeSinceLastLogicFrame(0),
		mCurrentTransformIdx(0),
		mThreadGameEntityToUpdate(nullptr),
		mThreadWeight(0),
		isInitializingLevel(false),
		initObjectCount(0),
		mQuit(false),
		mAlwaysAskForConfig(true),
		mBackgroundColour(backgroundColour) {

	}

    //-----------------------------------------------------------------------------------
    GraphicsSystem::~GraphicsSystem()
    {
        assert( !mRoot && "deinitialize() not called!!!" );
    }

	void GraphicsSystem::_notifyLogicSystem(BaseSystem* logicSystem) {
	    mLogicSystem = logicSystem;
    }	
	
	//-----------------------------------------------------------------------------------
    void GraphicsSystem::initialize( const Ogre::String &windowTitle )
    {
    #if OGRE_USE_SDL2
        if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        {
            OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
                         "GraphicsSystem::initialize" );
        }
    #endif

        Ogre::String pluginsPath;
        // only use plugins.cfg if not static
    #ifndef OGRE_STATIC_LIB
    #if OGRE_DEBUG_MODE
        pluginsPath = mResourcePath + "plugins_d.cfg";
    #else
        pluginsPath = mResourcePath + "plugins.cfg";
    #endif
    #endif

        mRoot = OGRE_NEW Ogre::Root( pluginsPath,
                                     mResourcePath + "ogre.cfg",
                                     mResourcePath + "Ogre.log" );

    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        mResourcePath = Ogre::macBundlePath() + '/';
    #endif

        mStaticPluginLoader.install( mRoot );

        if( mAlwaysAskForConfig || !mRoot->restoreConfig() )
        {
            if( !mRoot->showConfigDialog() )
            {
                mQuit = true;
                return;
            }
        }

    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        {
            Ogre::RenderSystem *renderSystem =
                    mRoot->getRenderSystemByName( "Metal Rendering Subsystem" );
            mRoot->setRenderSystem( renderSystem );
        }
    #endif

        mRoot->getRenderSystem()->setConfigOption( "sRGB Gamma Conversion", "Yes" );
        mRoot->initialise(false);

        Ogre::ConfigOptionMap& cfgOpts = mRoot->getRenderSystem()->getConfigOptions();

        int width   = 1280;
        int height  = 720;

    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        {
            Ogre::Vector2 screenRes = iOSUtils::getScreenResolutionInPoints();
            width = static_cast<int>( screenRes.x );
            height = static_cast<int>( screenRes.y );
        }
    #endif

        Ogre::ConfigOptionMap::iterator opt = cfgOpts.find( "Video Mode" );
        if( opt != cfgOpts.end() )
        {
            //Ignore leading space
            const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
            //Get the width and height
            Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
            // we know that the height starts 3 characters after the width and goes until the next space
            Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd+3);
            // Now we can parse out the values
            width   = Ogre::StringConverter::parseInt( opt->second.currentValue.substr( 0, widthEnd ) );
            height  = Ogre::StringConverter::parseInt( opt->second.currentValue.substr(
                                                           widthEnd+3, heightEnd ) );
        }

        Ogre::NameValuePairList params;
        bool fullscreen = Ogre::StringConverter::parseBool( cfgOpts["Full Screen"].currentValue );
    #if OGRE_USE_SDL2
        int screen = 0;
        int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
        int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

        if(fullscreen)
        {
            posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
            posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
        }

        mSdlWindow = SDL_CreateWindow(
                    windowTitle.c_str(),    // window title
                    posX,               // initial x position
                    posY,               // initial y position
                    width,              // width, in pixels
                    height,             // height, in pixels
                    SDL_WINDOW_SHOWN
                      | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE );

        //Get the native whnd
        SDL_SysWMinfo wmInfo;
        SDL_VERSION( &wmInfo.version );

        if( SDL_GetWindowWMInfo( mSdlWindow, &wmInfo ) == SDL_FALSE )
        {
            OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR,
                         "Couldn't get WM Info! (SDL2)",
                         "GraphicsSystem::initialize" );
        }

        Ogre::String winHandle;
        switch( wmInfo.subsystem )
        {
        #ifdef WIN32
        case SDL_SYSWM_WINDOWS:
            // Windows code
            winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.win.window );
            break;
        #elif __MACOSX__
        case SDL_SYSWM_COCOA:
            //required to make OGRE play nice with our window
            params.insert( std::make_pair("macAPI", "cocoa") );
            params.insert( std::make_pair("macAPICocoaUseNSView", "true") );

            winHandle  = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
            break;
        #else
        case SDL_SYSWM_X11:
            winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.x11.window );
            break;
        #endif
        default:
            OGRE_EXCEPT( Ogre::Exception::ERR_NOT_IMPLEMENTED,
                         "Unexpected WM! (SDL2)",
                         "GraphicsSystem::initialize" );
            break;
        }

        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            params.insert( std::make_pair("externalWindowHandle",  winHandle) );
        #else
            params.insert( std::make_pair("parentWindowHandle",  winHandle) );
        #endif
    #endif

        params.insert( std::make_pair("title", windowTitle) );
        params.insert( std::make_pair("gamma", "true") );
        params.insert( std::make_pair("FSAA", cfgOpts["FSAA"].currentValue) );
        params.insert( std::make_pair("vsync", cfgOpts["VSync"].currentValue) );

        mRenderWindow = Ogre::Root::getSingleton().createRenderWindow( windowTitle, width, height,
                                                                       fullscreen, &params );

        mOverlaySystem = OGRE_NEW Ogre::v1::OverlaySystem();

        setupResources();
        loadResources();
        chooseSceneManager();
        createCamera();
        mWorkspace = setupCompositor();

    #if OGRE_USE_SDL2
        mInputHandler = new SdlInputHandler( mSdlWindow, mCurrentGameState,
                                             mCurrentGameState, mCurrentGameState );
		mInputHandler->bindSystems(mLogicSystem, this);
    #endif

        BaseSystem::initialize();
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::deinitialize(void)
    {
        BaseSystem::deinitialize();

        if( mSceneManager )
            mSceneManager->removeRenderQueueListener( mOverlaySystem );

        OGRE_DELETE mOverlaySystem;
        mOverlaySystem = nullptr;

    #if OGRE_USE_SDL2
        delete mInputHandler;
        mInputHandler = nullptr;
    #endif

        OGRE_DELETE mRoot;
        mRoot = nullptr;

    #if OGRE_USE_SDL2
        if( mSdlWindow )
        {
            // Restore desktop resolution on exit
            SDL_SetWindowFullscreen( mSdlWindow, 0 );
            SDL_DestroyWindow( mSdlWindow );
            mSdlWindow = nullptr;
        }

        SDL_Quit();
    #endif
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::update( float timeSinceLast )
    {
        Ogre::WindowEventUtilities::messagePump();

    #if OGRE_USE_SDL2
        SDL_Event evt;
        while( SDL_PollEvent( &evt ) )
        {
            switch( evt.type )
            {
            case SDL_WINDOWEVENT:
                handleWindowEvent( evt );
                break;
            case SDL_QUIT:
                mQuit = true;
                break;
            default:
                break;
            }

            mInputHandler->_handleSdlEvents( evt );
        }
    #endif

        BaseSystem::update( timeSinceLast );

        if( mRenderWindow->isVisible() )
            mQuit |= !mRoot->renderOneFrame();

        mAccumTimeSinceLastLogicFrame += timeSinceLast;

        //SDL_SetWindowPosition( mSdlWindow, 0, 0 );
        /*SDL_Rect rect;
        SDL_GetDisplayBounds( 0, &rect );
        SDL_GetDisplayBounds( 0, &rect );*/
    }
    //-----------------------------------------------------------------------------------
    #if OGRE_USE_SDL2
    void GraphicsSystem::handleWindowEvent( const SDL_Event& evt )
    {
        switch( evt.window.event )
        {
            /*case SDL_WINDOWEVENT_MAXIMIZED:
                SDL_SetWindowBordered( mSdlWindow, SDL_FALSE );
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
            case SDL_WINDOWEVENT_RESTORED:
                SDL_SetWindowBordered( mSdlWindow, SDL_TRUE );
                break;*/
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                int w,h;
                SDL_GetWindowSize( mSdlWindow, &w, &h );
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
                mRenderWindow->resize( w, h );
#else
                mRenderWindow->windowMovedOrResized();
#endif
                break;
            case SDL_WINDOWEVENT_RESIZED:
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
                mRenderWindow->resize( evt.window.data1, evt.window.data2 );
#else
                mRenderWindow->windowMovedOrResized();
#endif
                break;
            case SDL_WINDOWEVENT_CLOSE:
                break;
            case SDL_WINDOWEVENT_SHOWN:
                mRenderWindow->setVisible(true);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                mRenderWindow->setVisible(false);
                break;
        }
    }
    #endif
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::processIncomingMessage( Mq::MessageType messageId, const void *data )
    {
        switch( messageId )
        {
        case Mq::LOGICFRAME_FINISHED:
            {
                Ogre::uint32 newIdx = *reinterpret_cast<const Ogre::uint32*>( data );

                if( newIdx != std::numeric_limits<Ogre::uint32>::max() )
                {
                    mAccumTimeSinceLastLogicFrame = 0;
                    //Tell the LogicSystem we're no longer using the index previous to the current one.
                    this->queueSendMessage( mLogicSystem, Mq::LOGICFRAME_FINISHED,
                                            (mCurrentTransformIdx + NUM_GAME_ENTITY_BUFFERS - 1) %
                                            NUM_GAME_ENTITY_BUFFERS );

                    assert( (mCurrentTransformIdx + 1) % NUM_GAME_ENTITY_BUFFERS == newIdx &&
                            "Graphics is receiving indices out of order!!!" );

                    //Get the new index the LogicSystem is telling us to use.
                    mCurrentTransformIdx = newIdx;
                }
            }
            break;
        case Mq::GAME_ENTITY_ADDED:
            gameEntityAdded( reinterpret_cast<const LevelManager::CreatedGameEntity*>( data ) );
            break;
        case Mq::GAME_ENTITY_REMOVED:
            gameEntityRemoved( *reinterpret_cast<GameEntity * const *>( data ) );
            break;
		case Mq::GAME_ENTITY_BIND:
			bindObject(*reinterpret_cast<LevelManager::BindDefinition* const*>(data));
			break;
        case Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT:
            //Acknowledge/notify back that we're done with this slot.
            this->queueSendMessage( mLogicSystem, Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
                                    *reinterpret_cast<const Ogre::uint32*>( data ) );
            break;
		case Mq::INIT_LEVEL_START:
			isInitializingLevel = true;
			initObjectCount = *reinterpret_cast<const int*>(data);
			break;
		case Mq::SHOW_GAME_UI:
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->musicUIManager->showMusicUI(true);
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->gameUIManager->showGameUI(true);
			break;
		case Mq::SHOW_SEQUENCE_RESULT:
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->musicUIManager->showResult(*reinterpret_cast<const ControlState*>(data));
			break;
		case Mq::CAMERA_FOLLOW_PATH:
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->mainCameraPathController->bindPath(*reinterpret_cast<Path* const*>(data));
			break;
        case Mq::CAMERA_FOLLOW_CHARACTER:
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->mainCameraPathController->bindCharacter(*reinterpret_cast<Unit* const*>(data));
			break;
		case Mq::CAMERA_FOLLOW_ENABLE:
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->mainCameraPathController->isEnabled = true;
			reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->mainCameraPathController->reset();
			break;
		case Mq::CAMERA_FOLLOW_CLEAR:
        	{
				CameraPathController* mcpc = reinterpret_cast<ZSGraphicsGameState*>(mCurrentGameState)->mainCameraPathController;
				mcpc->isEnabled = false;
				mcpc->bindPath(nullptr);
				mcpc->bindCharacter(nullptr);
			}
			break;
		case Mq::GAME_ENTITY_PLAY_ANIMATION:
			{
				AnimationController::AnimationInstruction* aci = *reinterpret_cast<AnimationController::AnimationInstruction* const*>(data);
				aci->ac->startAnimation(aci->state, aci->loop);
			}
			break;
		case Mq::UNLOAD_LEVEL:
			mGameEntities[Ogre::SCENE_STATIC].clear();
			mGameEntities[Ogre::SCENE_DYNAMIC].clear();
			break;
        default:
            break;
        }
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::addResourceLocation( const Ogre::String &archName, const Ogre::String &typeName,
                                              const Ogre::String &secName )
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        // OS X does not set the working directory relative to the app,
        // In order to make things portable on OS X we need to provide
        // the loading with it's own bundle path location
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    Ogre::String( Ogre::macBundlePath() + "/" + archName ), typeName, secName );
#else
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
#endif
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::setupResources(void)
    {
        // Load resource paths from config file
        Ogre::ConfigFile cf;
        cf.load(mResourcePath + "resources2.cfg");

        // Go through all sections & settings in the file
        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

        Ogre::String secName, typeName, archName;
        while( seci.hasMoreElements() )
        {
            secName = seci.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

            if( secName != "Hlms" )
            {
                Ogre::ConfigFile::SettingsMultiMap::iterator i;
                for (i = settings->begin(); i != settings->end(); ++i)
                {
                    typeName = i->first;
                    archName = i->second;
                    addResourceLocation( archName, typeName, secName );
                }
            }
        }
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::registerHlms(void)
    {
        Ogre::ConfigFile cf;
        cf.load( mResourcePath + "resources2.cfg" );

        Ogre::String dataFolder = mResourcePath + cf.getSetting( "DoNotUseAsResource", "Hlms", "" );

        if( dataFolder.empty() )
            dataFolder = "./";
        else if( *(dataFolder.end() - 1) != '/' )
            dataFolder += "/";

        Ogre::RenderSystem *renderSystem = mRoot->getRenderSystem();

        Ogre::String shaderSyntax = "GLSL";
        if( renderSystem->getName() == "Direct3D11 Rendering Subsystem" )
            shaderSyntax = "HLSL";
        else if( renderSystem->getName() == "Metal Rendering Subsystem" )
            shaderSyntax = "Metal";

        Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
                        dataFolder + "Hlms/Common/" + shaderSyntax,
                        "FileSystem", true );
        Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(
                        dataFolder + "Hlms/Common/Any",
                        "FileSystem", true );

        Ogre::ArchiveVec library;
        library.push_back( archiveLibrary );
        library.push_back( archiveLibraryAny );

        Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(
                        dataFolder + "Hlms/Unlit/" + shaderSyntax,
                        "FileSystem", true );

        Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit( archiveUnlit, &library );
        Ogre::Root::getSingleton().getHlmsManager()->registerHlms( hlmsUnlit );

        Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(
                        dataFolder + "Hlms/Pbs/" + shaderSyntax,
                        "FileSystem", true );
        Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs( archivePbs, &library );
        Ogre::Root::getSingleton().getHlmsManager()->registerHlms( hlmsPbs );

        if( renderSystem->getName() == "Direct3D11 Rendering Subsystem" )
        {
            //Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
            //and below to avoid saturating AMD's discard limit (8MB) or
            //saturate the PCIE bus in some low end machines.
            bool supportsNoOverwriteOnTextureBuffers;
            renderSystem->getCustomAttribute( "MapNoOverwriteOnDynamicBufferSRV",
                                              &supportsNoOverwriteOnTextureBuffers );

            if( !supportsNoOverwriteOnTextureBuffers )
            {
                hlmsPbs->setTextureBufferDefaultSize( 512 * 1024 );
                hlmsUnlit->setTextureBufferDefaultSize( 512 * 1024 );
            }
        }
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::loadResources(void)
    {
        registerHlms();

        // Initialise, parse scripts etc
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::chooseSceneManager(void)
    {
        Ogre::InstancingThreadedCullingMethod threadedCullingMethod =
                Ogre::INSTANCING_CULLING_SINGLETHREAD;
#if !OGRE_DEBUG_MODE
        //Debugging multithreaded code is a PITA, disable it.
        const size_t numThreads = 1;
#else
        //getNumLogicalCores() may return 0 if couldn't detect
        const size_t numThreads = std::max<size_t>( 1, Ogre::PlatformInformation::getNumLogicalCores() );
        //See doxygen documentation regarding culling methods.
        //In some cases you may still want to use single thread.
        //if( numThreads > 1 )
        //	threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
#endif
        // Create the SceneManager, in this case a generic one
        mSceneManager = mRoot->createSceneManager( Ogre::ST_GENERIC,
                                                   numThreads,
                                                   threadedCullingMethod,
                                                   "ExampleSMInstance" );

        mSceneManager->addRenderQueueListener( mOverlaySystem );

        //Set sane defaults for proper shadow mapping
        mSceneManager->setShadowDirectionalLightExtrusionDistance( 500.0f );
        mSceneManager->setShadowFarDistance( 500.0f );
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::createCamera(void)
    {
        mCamera = mSceneManager->createCamera( "Main Camera" );

        // Position it at 500 in Z direction
        mCamera->setPosition( Ogre::Vector3( 0, 5, 15 ) );
        // Look back along -Z
        mCamera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
        mCamera->setNearClipDistance( 0.2f );
        mCamera->setFarClipDistance( 1000.0f );
        mCamera->setAutoAspectRatio( true );
    }
    //-----------------------------------------------------------------------------------
    Ogre::CompositorWorkspace* GraphicsSystem::setupCompositor(void)
    {
        Ogre::CompositorManager2 *compositorManager = mRoot->getCompositorManager2();

        const Ogre::IdString workspaceName( "ZS Workspace" );
        if( !compositorManager->hasWorkspaceDefinition( workspaceName ) )
        {
            compositorManager->createBasicWorkspaceDef( workspaceName, mBackgroundColour,
                                                        Ogre::IdString() );
        }

        return compositorManager->addWorkspace( mSceneManager, mRenderWindow, mCamera,
                                                workspaceName, true );
    }
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    struct GameEntityCmp
    {
        bool operator () ( const GameEntity *_l, const Ogre::Matrix4 * RESTRICT_ALIAS _r ) const
        {
            const Ogre::Transform &transform = _l->mSceneNode->_getTransform();
            return &transform.mDerivedTransform[transform.mIndex] < _r;
        }

        bool operator () ( const Ogre::Matrix4 * RESTRICT_ALIAS _r, const GameEntity *_l ) const
        {
            const Ogre::Transform &transform = _l->mSceneNode->_getTransform();
            return _r < &transform.mDerivedTransform[transform.mIndex];
        }

        bool operator () ( const GameEntity *_l, const GameEntity *_r ) const
        {
            const Ogre::Transform &lTransform = _l->mSceneNode->_getTransform();
            const Ogre::Transform &rTransform = _r->mSceneNode->_getTransform();
            return &lTransform.mDerivedTransform[lTransform.mIndex] < &rTransform.mDerivedTransform[rTransform.mIndex];
        }
    };
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::gameEntityAdded( const LevelManager::CreatedGameEntity *cge )
    {
        Ogre::SceneNode *sceneNode = mSceneManager->getRootSceneNode( cge->gameEntity->mType )->
                createChildSceneNode( cge->gameEntity->mType,
                                      cge->initialTransform.vPos,
                                      cge->initialTransform.qRot );

        sceneNode->setScale( cge->initialTransform.vScale );

        cge->gameEntity->mSceneNode = sceneNode;

        if( cge->gameEntity->mMoDefinition->moType == MoTypeItem
			|| cge->gameEntity->mMoDefinition->moType == MoTypeItemInk
			|| cge->gameEntity->mMoDefinition->moType == MoTypeItemSkeleton)
        {
            Ogre::Item *item = mSceneManager->createItem( cge->gameEntity->mMoDefinition->meshName,
                                                          cge->gameEntity->mMoDefinition->resourceGroup,
                                                          cge->gameEntity->mType );

			if(cge->gameEntity->mMoDefinition->moType == MoTypeItemInk)
				item->setDatablock("InkShader");

            Ogre::StringVector materialNames = cge->gameEntity->mMoDefinition->submeshMaterials;
            size_t minMaterials = std::min( materialNames.size(), item->getNumSubItems() );

            for( size_t i=0; i<minMaterials; ++i )
            {
                item->getSubItem(i)->setDatablockOrMaterialName( materialNames[i],
                                                                 cge->gameEntity->mMoDefinition->
                                                                                    resourceGroup );
            }

			if(cge->gameEntity->mMoDefinition->moType == MoTypeItemSkeleton) {
				if(item->hasSkeleton() && item->getSkeletonInstance()->getAnimations().size() > 0) {
					cge->gameEntity->hasAnimation = true;
					cge->gameEntity->animationController = new AnimationController(item->getSkeletonInstance());
				} else {
					cge->gameEntity->hasAnimation = false;
				}
			}
            cge->gameEntity->mMovableObject = item;
        }

		if(cge->gameEntity->mMoDefinition->moType == MoTypeItemV1Mesh || cge->gameEntity->mMoDefinition->moType == MoTypeItemV1MeshTAMWrap) {
			Ogre::Item *item;

			if(Ogre::MeshManager::getSingleton().getResourceByName(cge->gameEntity->mMoDefinition->meshName) == nullptr) {
				Ogre::v1::MeshPtr meshV1 = Ogre::v1::MeshManager::getSingleton().load(cge->gameEntity->mMoDefinition->meshName,
																					  Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
																					  Ogre::v1::HardwareBuffer::HBU_STATIC,
																					  Ogre::v1::HardwareBuffer::HBU_STATIC);

				Ogre::MeshPtr meshV2 = Ogre::MeshManager::getSingleton().createManual(cge->gameEntity->mMoDefinition->meshName,
																					  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
				meshV2->importV1(meshV1.get(), true, true, true);

				item = mSceneManager->createItem(meshV2, Ogre::SCENE_STATIC);
			} else {
				item = mSceneManager->createItem(cge->gameEntity->mMoDefinition->meshName,
												 Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
												 Ogre::SCENE_STATIC);
			}
			
			Ogre::StringVector materialNames = cge->gameEntity->mMoDefinition->submeshMaterials;
			size_t minMaterials = std::min(materialNames.size(), item->getNumSubItems());

			for(size_t i = 0; i<minMaterials; ++i) {
				item->getSubItem(i)->setDatablockOrMaterialName(materialNames[i],
																cge->gameEntity->mMoDefinition->
																resourceGroup);
				
				
				if(cge->gameEntity->mMoDefinition->moType == MoTypeItemV1MeshTAMWrap) {
					Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(
						item->getSubItem(i)->getDatablock());
					//Make a hard copy of the sampler block
					Ogre::HlmsSamplerblock samplerblock(*datablock->getSamplerblock(0));
					samplerblock.mU = Ogre::TAM_WRAP;
					samplerblock.mV = Ogre::TAM_WRAP;
					samplerblock.mW = Ogre::TAM_WRAP;
					//Set the new samplerblock. The Hlms system will
					//automatically create the API block if necessary
					datablock->setSamplerblock(0, samplerblock);
				}
			}

			cge->gameEntity->mMovableObject = item;
		}

        sceneNode->attachObject( cge->gameEntity->mMovableObject );

		if(isInitializingLevel) {
			--initObjectCount;
			if(initObjectCount == 0) {
				isInitializingLevel = false;
				queueSendMessage(mLogicSystem, Mq::INIT_LEVEL_DONE, nullptr);
			}
		}

        //Keep them sorted on how Ogre's internal memory manager assigned them memory,
        //to avoid false cache sharing when we update the nodes concurrently.
        const Ogre::Transform &transform = sceneNode->_getTransform();
        GameEntityVec::iterator itGameEntity = std::lower_bound(
                    mGameEntities[cge->gameEntity->mType].begin(),
                    mGameEntities[cge->gameEntity->mType].end(),
                    &transform.mDerivedTransform[transform.mIndex],
                    GameEntityCmp() );
        mGameEntities[cge->gameEntity->mType].insert( itGameEntity, cge->gameEntity );
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::gameEntityRemoved( GameEntity *toRemove )
    {
        const Ogre::Transform &transform = toRemove->mSceneNode->_getTransform();

		GameEntityVec::iterator itGameEntity = std::find(
			mGameEntities[toRemove->mType].begin(),
			mGameEntities[toRemove->mType].end(),
			toRemove);

        /*GameEntityVec::iterator itGameEntity = std::lower_bound(
                    mGameEntities[toRemove->mType].begin(),
                    mGameEntities[toRemove->mType].end(),
                    &transform.mDerivedTransform[transform.mIndex],
                    GameEntityCmp() );*/

        assert( itGameEntity != mGameEntities[toRemove->mType].end() && *itGameEntity == toRemove );
        mGameEntities[toRemove->mType].erase( itGameEntity );

        toRemove->mSceneNode->getParentSceneNode()->removeAndDestroyChild( toRemove->mSceneNode );
        toRemove->mSceneNode = nullptr;

        assert( dynamic_cast<Ogre::Item*>( toRemove->mMovableObject ) );

        mSceneManager->destroyItem( static_cast<Ogre::Item*>( toRemove->mMovableObject ) );
        toRemove->mMovableObject = nullptr;
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::updateGameEntities( const GameEntityVec &gameEntities, float weight )
    {
        mThreadGameEntityToUpdate   = &gameEntities;
        mThreadWeight               = weight;

		//Note: You could execute a non-blocking scalable task and do something else, you should
        //wait for the task to finish right before calling renderOneFrame or before trying to
        //execute another UserScalableTask (you would have to be careful, but it could work).
        mSceneManager->executeUserScalableTask( this, true );
    }
    //-----------------------------------------------------------------------------------
    void GraphicsSystem::execute( size_t threadId, size_t numThreads )
    {
        size_t currIdx = mCurrentTransformIdx;
        size_t prevIdx = (mCurrentTransformIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

        const size_t objsPerThread = (mThreadGameEntityToUpdate->size() + (numThreads - 1)) / numThreads;
        const size_t toAdvance = std::min( threadId * objsPerThread, mThreadGameEntityToUpdate->size() );

        GameEntityVec::const_iterator itor = mThreadGameEntityToUpdate->begin() + toAdvance;
        GameEntityVec::const_iterator end  = mThreadGameEntityToUpdate->begin() +
                                                                std::min( toAdvance + objsPerThread,
                                                                          mThreadGameEntityToUpdate->size() );
        while( itor != end )
        {
            GameEntity *gEnt = *itor;
            Ogre::Vector3 interpVec = Ogre::Math::lerp( gEnt->mTransform[prevIdx]->vPos,
                                                        gEnt->mTransform[currIdx]->vPos, mThreadWeight );
            gEnt->mSceneNode->setPosition( interpVec );

            interpVec = Ogre::Math::lerp( gEnt->mTransform[prevIdx]->vScale,
                                          gEnt->mTransform[currIdx]->vScale, mThreadWeight );
            gEnt->mSceneNode->setScale( interpVec );

            Ogre::Quaternion interpQ = Ogre::Math::lerp( gEnt->mTransform[prevIdx]->qRot,
                                                         gEnt->mTransform[currIdx]->qRot, mThreadWeight );
            gEnt->mSceneNode->setOrientation( interpQ );

			if(gEnt->hasAnimation && gEnt->animationController->isEnabled) {
				gEnt->animationController->update(0.01667f * mThreadWeight);
			}

            ++itor;
        }
    }

	void GraphicsSystem::bindObject(const LevelManager::BindDefinition* bd) {
		Ogre::TagPoint* bindTagPoint = mSceneManager->createTagPoint();
		bd->source->mSceneNode->getParentSceneNode()->removeChild(bd->source->mSceneNode);
		bindTagPoint->addChild(bd->source->mSceneNode);
		bd->target->mMovableObject->getSkeletonInstance()->getBone(bd->boneName)->addTagPoint(bindTagPoint);
    }
}
