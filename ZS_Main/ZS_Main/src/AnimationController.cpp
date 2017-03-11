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
		if(_state.compare("_CURRENT") != 0) {
			changeAnimation(_state);
		}

		isEnabled = true;
		currentAnim->setEnabled(true);
		currentAnim->mFrameRate = _playbackSpeed;
	}

	void AnimationController::changeAnimation(Ogre::String _state) {
		if(skeleton->hasAnimation(_state)) {
			currentAnim->setEnabled(false);
			currentAnim = skeleton->getAnimation(_state);
			currentAnim->setTime(0.0f);
			currentState = _state;
			currentAnim->setEnabled(true);
		}
	}

	void AnimationController::stopAnimation() {
		isEnabled = false;
		currentAnim->setEnabled(false);
	}

	void AnimationController::update(float timeSinceLast) {
		if(isEnabled)
			currentAnim->addTime(timeSinceLast);
	}
}
