/**
 * Project ZS
 */


#ifndef _ZS_ITEM_H
#define _ZS_ITEM_H

#include "GameObject.h"

namespace ZS {

	class Item : public GameObject {
	public:
		int id;

		Item(std::string _name, int _id);
		~Item();
		
	};
}

#endif //_ITEM_H