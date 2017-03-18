﻿#ifndef _ZS_UIELEMENT_H
#define _ZS_UIELEMENT_H
#include "OgreOverlayContainer.h"

namespace ZS {
	// For bar(hp) modification encapsulation
	class UIElement {
	private:
		Ogre::v1::OverlayContainer* element;

	public:
		UIElement();
		~UIElement();

		void fill();
		void lerp();
		void update(float timeSinceLast);
	};

}

#endif
