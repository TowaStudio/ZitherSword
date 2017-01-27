/**
 * Project ZS
 */

#ifndef _AUDIOSYSTEM_H
#define _AUDIOSYSTEM_H

namespace ZS {
	class AudioSystem {
	private:
		static AudioSystem* instance;
		AudioSystem();
		AudioSystem(AudioSystem const&) {};
		AudioSystem& operator= (AudioSystem const&) {};

	public:
		static AudioSystem* GetInstance() {
			return instance;
		}
	};
}

#endif //_AUDIOSYSTEM_H
