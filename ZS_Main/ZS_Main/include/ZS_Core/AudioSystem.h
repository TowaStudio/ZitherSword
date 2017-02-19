/**
 * Project ZS
 */

#ifndef _ZS_AUDIOSYSTEM_H
#define _ZS_AUDIOSYSTEM_H

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
