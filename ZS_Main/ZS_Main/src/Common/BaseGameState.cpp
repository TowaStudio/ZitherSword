
#include "BaseGameState.h"
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

using namespace ZS;

namespace ZS
{
    BaseGameState::BaseGameState( const Ogre::String &helpDescription ) :
        mGraphicsSystem( 0 ),
        mCameraController( 0 ),
        mHelpDescription( helpDescription ),
        mDebugText( 0 )
    {
    }
    //-----------------------------------------------------------------------------------
    BaseGameState::~BaseGameState()
    {
        delete mCameraController;
        mCameraController = 0;
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::_notifyGraphicsSystem( GraphicsSystem *graphicsSystem )
    {
        mGraphicsSystem = graphicsSystem;
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::createScene01(void)
    {
        createDebugTextOverlay();
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::createDebugTextOverlay(void)
    {
        Ogre::v1::OverlayManager &overlayManager = Ogre::v1::OverlayManager::getSingleton();
        Ogre::v1::Overlay *overlay = overlayManager.create( "DebugText" );

        Ogre::v1::OverlayContainer *panel = static_cast<Ogre::v1::OverlayContainer*>(
            overlayManager.createOverlayElement("Panel", "DebugPanel"));
        mDebugText = static_cast<Ogre::v1::TextAreaOverlayElement*>(
                    overlayManager.createOverlayElement( "TextArea", "DebugText" ) );
        mDebugText->setFontName( "Helvetica" );
        mDebugText->setCharHeight( 0.03f );

        mDebugTextShadow= static_cast<Ogre::v1::TextAreaOverlayElement*>(
                    overlayManager.createOverlayElement( "TextArea", "0DebugTextShadow" ) );
        mDebugTextShadow->setFontName( "Helvetica" );
        mDebugTextShadow->setCharHeight( 0.03f );
        mDebugTextShadow->setColour( Ogre::ColourValue::Black );
        mDebugTextShadow->setPosition( 0.001f, 0.001f );

        panel->addChild( mDebugTextShadow );
        panel->addChild( mDebugText );
        overlay->add2D( panel );
        overlay->show();
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::generateDebugText( float timeSinceLast, Ogre::String &outText )
    {
        const Ogre::FrameStats *frameStats = mGraphicsSystem->getRoot()->getFrameStats();

        Ogre::String finalText;
        finalText.reserve( 128 );
        finalText  = "Frame time:\t";
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
    //-----------------------------------------------------------------------------------
    void BaseGameState::update( float timeSinceLast )
    {
        //Show FPS
        Ogre::String finalText;
        generateDebugText( timeSinceLast, finalText );
        mDebugText->setCaption( finalText );
        mDebugTextShadow->setCaption( finalText );

        if( mCameraController )
            mCameraController->update( timeSinceLast );
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::keyPressed( const SDL_KeyboardEvent &arg )
    {
        bool handledEvent = false;

        if( mCameraController )
            handledEvent = mCameraController->keyPressed( arg );

        if( !handledEvent )
            GameState::keyPressed( arg );
    }
    //-----------------------------------------------------------------------------------
    void BaseGameState::keyReleased( const SDL_KeyboardEvent &arg )
    {
        if( arg.keysym.sym == SDLK_F1 && (arg.keysym.mod & ~(KMOD_NUM|KMOD_CAPS)) == 0 )
        {
            Ogre::String finalText;
            generateDebugText( 0, finalText );
            mDebugText->setCaption( finalText );
            mDebugTextShadow->setCaption( finalText );
        }
        else if( arg.keysym.sym == SDLK_F1 && (arg.keysym.mod & (KMOD_LCTRL|KMOD_RCTRL)) )
        {
            //Hot reload of PBS shaders. We need to clear the microcode cache
            //to prevent using old compiled versions.
            Ogre::Root *root = mGraphicsSystem->getRoot();
            Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

            Ogre::Hlms *hlms = hlmsManager->getHlms( Ogre::HLMS_PBS );
            Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
            hlms->reloadFrom( hlms->getDataFolder() );
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
        else if( arg.keysym.sym == SDLK_F3 && (arg.keysym.mod & (KMOD_LCTRL|KMOD_RCTRL)) )
        {
            //Hot reload of Unlit shaders.
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
    void BaseGameState::mouseMoved( const SDL_Event &arg )
    {
        if( mCameraController )
            mCameraController->mouseMoved( arg );

        GameState::mouseMoved( arg );
    }
}
