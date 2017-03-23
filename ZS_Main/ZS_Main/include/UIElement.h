#ifndef _ZS_UIELEMENT_H
#define _ZS_UIELEMENT_H
#include "OgreOverlayElement.h"

namespace ZS {
	class UIElement {
	private:
		Ogre::v1::OverlayElement* element;

	public:
		UIElement();
		~UIElement();

		void update(float timeSinceLast);
	};

}

#endif
