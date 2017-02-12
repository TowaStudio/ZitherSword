/**
 * Project ZS
 */


#include "AudioSystem.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();

	AudioSystem::AudioSystem() {
		time = 0;
	}
	
	void AudioSystem::timerCallback() {
		time++;
	}
}
