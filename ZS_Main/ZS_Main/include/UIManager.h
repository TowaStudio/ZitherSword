#ifndef _ZS_UIMANAGER_H
#define _ZS_UIMANAGER_H

namespace ZS {
	class UIManager {
	private:
		static UIManager* instance;
		UIManager();
		UIManager(UIManager const&) {}
		UIManager& operator= (UIManager const&) {}

	public:
		static UIManager GetInstance() {
			return instance;
		}

	};
}

#endif
