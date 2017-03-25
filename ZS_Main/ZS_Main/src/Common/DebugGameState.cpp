
#include "DebugGameState.h"
#include "CameraController.h"
#include "GraphicsSystem.h"

#include "OgreSceneManager.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"

#include "OgreRoot.h"
#include "OgreFrameStats.h"

#include "OgreHlmsManager.h"
#include "OgreHlms.h"
#include "OgreHlmsCompute.h"
#include "OgreGpuProgramManager.h"
#include "GameMaster.h"

using namespace ZS;

namespace ZS
{
    DebugGameState::DebugGameState() :
        mGraphicsSystem( nullptr ),
        mCameraController( nullptr ),
        mDebugText( nullptr ),
		mDebugTextShadow( nullptr ),
		consoleContent( "" )
    {
    }
    //-----------------------------------------------------------------------------------
    DebugGameState::~DebugGameState()
    {
        delete mCameraController;
        mCameraController = nullptr;
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::_notifyGraphicsSystem( GraphicsSystem *graphicsSystem )
    {
        mGraphicsSystem = graphicsSystem;
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::createScene01(void)
    {
        createDebugTextOverlay();
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::createDebugTextOverlay(void)
    {
        Ogre::v1::OverlayManager &overlayManager = Ogre::v1::OverlayManager::getSingleton();
        Ogre::v1::Overlay *overlay = overlayManager.create( "DebugText" );

        Ogre::v1::OverlayContainer *panel = static_cast<Ogre::v1::OverlayContainer*>(
            overlayManager.createOverlayElement("Panel", "DebugPanel"));
        mDebugText = static_cast<Ogre::v1::TextAreaOverlayElement*>(
                    overlayManager.createOverlayElement( "TextArea", "DebugText" ) );
        mDebugText->setFontName( "Helvetica" );
		mDebugText->setCharHeight( 0.03f );
		mDebugText->setColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
		mDebugText->setPosition(0.8f, 0.015f);

        mDebugTextShadow= static_cast<Ogre::v1::TextAreaOverlayElement*>(
                    overlayManager.createOverlayElement( "TextArea", "DebugTextShadow" ) );
        mDebugTextShadow->setFontName( "Helvetica" );
        mDebugTextShadow->setCharHeight( 0.03f );
        mDebugTextShadow->setColour( Ogre::ColourValue::Black );
        mDebugTextShadow->setPosition( 0.8005f, 0.0155f );

        panel->addChild( mDebugTextShadow );
        panel->addChild( mDebugText );
        overlay->add2D( panel );
        overlay->show();
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::showFPS( float timeSinceLast, Ogre::String &outText )
    {
        const Ogre::FrameStats *frameStats = mGraphicsSystem->getRoot()->getFrameStats();

        Ogre::String finalText(consoleContent);
        finalText.reserve( 128 );
        finalText += "\n\nFrame time:\t";
        finalText += Ogre::StringConverter::toString( timeSinceLast * 1000.0f );
        finalText += " ms\n";
        finalText += "Frame FPS:\t";
        finalText += Ogre::StringConverter::toString( 1.0f / timeSinceLast );
        finalText += "\nAvg time:\t";
        finalText += Ogre::StringConverter::toString( frameStats->getAvgTime() );
        finalText += " ms\n";
        finalText += "Avg FPS:\t";
        finalText += Ogre::StringConverter::toString( 1000.0f / frameStats->getAvgTime() );
        finalText += "\n";
        outText.swap( finalText );

        mDebugText->setCaption( finalText );
        mDebugTextShadow->setCaption( finalText );
    }

	void DebugGameState::log(Ogre::String content) {
		consoleContent = content;
	}

	//-----------------------------------------------------------------------------------
    void DebugGameState::update( float timeSinceLast )
    {
        //Show FPS
        Ogre::String finalText;
        showFPS( timeSinceLast, finalText );
        mDebugText->setCaption( finalText );
        mDebugTextShadow->setCaption( finalText );

        if( mCameraController )
            mCameraController->update( timeSinceLast );
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::keyPressed( const SDL_KeyboardEvent &arg )
    {
        bool handledEvent = false;

        if( mCameraController )
            handledEvent = mCameraController->keyPressed( arg );

        if( !handledEvent )
            GameState::keyPressed( arg );
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::keyReleased( const SDL_KeyboardEvent &arg )
    {
        if( arg.keysym.sym == SDLK_F1 && (arg.keysym.mod & ~(KMOD_NUM|KMOD_CAPS)) == 0 )
        {
            //Hot reload of Ink shaders.
            Ogre::Root *root = mGraphicsSystem->getRoot();
            Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

            Ogre::Hlms *hlms = hlmsManager->getHlms( Ogre::HLMS_USER0 );
            Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
            hlms->reloadFrom( hlms->getDataFolder() );
			GameMaster::GetInstance()->log(hlms->getDataFolder()->getName());
        }
        else if( arg.keysym.sym == SDLK_F2 && (arg.keysym.mod & (KMOD_LCTRL|KMOD_RCTRL)) )
        {
            //Hot reload of Unlit shaders.
            Ogre::Root *root = mGraphicsSystem->getRoot();
            Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

            Ogre::Hlms *hlms = hlmsManager->getHlms( Ogre::HLMS_UNLIT );
            Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
            hlms->reloadFrom( hlms->getDataFolder() );
        }
		else if(arg.keysym.sym == SDLK_F3 && (arg.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL))) {
			//Hot reload of PBS shaders. We need to clear the microcode cache
			//to prevent using old compiled versions.
			Ogre::Root *root = mGraphicsSystem->getRoot();
			Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

			Ogre::Hlms *hlms = hlmsManager->getHlms(Ogre::HLMS_PBS);
			Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
			hlms->reloadFrom(hlms->getDataFolder());
		}
        else if( arg.keysym.sym == SDLK_F4 && (arg.keysym.mod & (KMOD_LCTRL|KMOD_RCTRL)) )
        {
            //Hot reload of compute shaders.
            Ogre::Root *root = mGraphicsSystem->getRoot();
            Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

            Ogre::Hlms *hlms = hlmsManager->getComputeHlms();
            Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
            hlms->reloadFrom( hlms->getDataFolder() );
        }
        else
        {
            bool handledEvent = false;

            if( mCameraController )
                handledEvent = mCameraController->keyReleased( arg );

            if( !handledEvent )
                GameState::keyReleased( arg );
        }
    }
    //-----------------------------------------------------------------------------------
    void DebugGameState::mouseMoved( const SDL_Event &arg )
    {
        if( mCameraController )
            mCameraController->mouseMoved( arg );

        GameState::mouseMoved( arg );
    }
}
