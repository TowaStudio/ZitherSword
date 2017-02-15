
#ifndef _Demo_TutorialGameState_H_
#define _Demo_TutorialGameState_H_

#include "OgrePrerequisites.h"
#include "GameState.h"

namespace Ogre
{
    namespace v1
    {
        class TextAreaOverlayElement;
    }
}

namespace ZS
{
    class GraphicsSystem;
    class CameraController;

    /// Debug graphics gamestate.
    class DebugGameState : public GameState
    {
    protected:
        GraphicsSystem      *mGraphicsSystem;
        CameraController    *mCameraController;

        Ogre::v1::TextAreaOverlayElement *mDebugText;
        Ogre::v1::TextAreaOverlayElement *mDebugTextShadow;
		Ogre::String consoleContent;
		int count = 0;

        virtual void createDebugTextOverlay(void);
        virtual void showFPS( float timeSinceLast, Ogre::String &outText );

    public:
        DebugGameState();
        virtual ~DebugGameState();

        void _notifyGraphicsSystem( GraphicsSystem *graphicsSystem );

		void log(Ogre::String content);

        virtual void createScene01(void);

        virtual void update( float timeSinceLast );

        virtual void keyPressed( const SDL_KeyboardEvent &arg );
        virtual void keyReleased( const SDL_KeyboardEvent &arg );

        virtual void mouseMoved( const SDL_Event &arg );
    };
}

#endif
