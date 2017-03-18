#ifndef _ZS_UIBAR_H
#define _ZS_UIBAR_H
#include "UIElement.h"

namespace ZS {
	class UIBar : public UIElement {
	private:
		float currentFill;
		float targetFill;

	public:
		UIBar();
		~UIBar();

		void setFill(float _fill);
		void update(float timeSinceLast);
	};
}

#endif
