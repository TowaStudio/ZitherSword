#include "AnimationController.h"
#include "OgreMovableObject.h"

namespace ZS {

	AnimationController::AnimationController(Ogre::SkeletonInstance* _skeleton) :
		skeleton(_skeleton),
		isEnabled(false),
		currentState(""),
		currentAnim(nullptr)
	{
		if(skeleton->getAnimations().size() < 1)
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "No animations found for character controller", "AnimationController");

		/*currentState = skeleton->getAnimations()[0].getName().getFriendlyText();
		currentAnim = skeleton->getAnimation(currentState);*/
	}

	AnimationController::~AnimationController() {
	}

	void AnimationController::startAnimation(Ogre::String _state, bool _loop, float _playbackSpeed) {
		/*
		 * BUG: Active animations iterator will return null pointer during update.
		 * This may be related to the thread operations.
		*/ 
		// TODO: send message to graphics system to control the animation
		stopAnimation();
		if(_state.compare("_CURRENT") == 0) {
			currentAnim->setTime(0.0f);
			isEnabled = true;
			currentAnim->setLoop(_loop);
			currentAnim->setEnabled(true);
		} else if(skeleton->hasAnimation(_state)) {
			currentAnim = skeleton->getAnimation(_state);
			currentState = _state;

			currentAnim->setTime(0.0f);
			currentAnim->setLoop(_loop);
			currentAnim->setEnabled(true);
			isEnabled = true;
		}

		currentAnim->mFrameRate = 4.0f;
	}

	void AnimationController::stopAnimation() {
		isEnabled = false;
		if(currentAnim)
			currentAnim->setEnabled(false);
	}

	void AnimationController::update(float timeSinceLast) {
		if(isEnabled)
			currentAnim->addTime(timeSinceLast);
	}
}
