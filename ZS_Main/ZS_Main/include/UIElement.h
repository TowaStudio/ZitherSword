#ifndef _ZS_UIELEMENT_H
#define _ZS_UIELEMENT_H
#include "OgreOverlayContainer.h"

namespace ZS {
	class UIElement {
	private:
		Ogre::v1::OverlayContainer* element;

	public:
		UIElement();
		~UIElement();

		void update(float timeSinceLast);
	};

}

#endif
