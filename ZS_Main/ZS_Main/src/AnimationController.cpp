#include "AnimationController.h"
#include "OgreMovableObject.h"

namespace ZS {

	AnimationController::AnimationController(Ogre::SkeletonInstance* _skeleton) :
		skeleton(_skeleton),
		isEnabled(false)
	{
		if(skeleton->getAnimations().size() < 1)
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "No animations found for character controller", "AnimationController");

		currentState = skeleton->getAnimations()[0].getName().getFriendlyText();
		currentAnim = skeleton->getAnimation(currentState);
	}

	AnimationController::~AnimationController() {
	}

	void AnimationController::startAnimation(Ogre::String _state, float _playbackSpeed) {
		if(_state.compare("_CURRENT") == 0) {
			currentAnim->setTime(0.0f);
			isEnabled = true;
			currentAnim->setEnabled(true);
		} else if(skeleton->hasAnimation(_state)) {
			stopAnimation();
			currentAnim = skeleton->getAnimation(_state);
			currentState = _state;

			currentAnim->setTime(0.0f);
			isEnabled = true;
			currentAnim->setEnabled(true);
		}

		currentAnim->mFrameRate = 3.0f;
	}

	void AnimationController::stopAnimation() {
		isEnabled = false;
		currentAnim->setEnabled(false);
	}

	void AnimationController::update(float timeSinceLast) {
		currentAnim->addTime(timeSinceLast);
	}
}
