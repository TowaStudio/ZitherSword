/**
 * Project ZS
 */


#ifndef _ZS_FLYINGPROPS_H
#define _ZS_FLYINGPROPS_H

#include "Item.h"

namespace ZS {
	class FlyingProps : public Item {
	public:
		FlyingProps(const std::string& _name, int _id, float _atk)
			: Item(_name, _id),
			  atk(_atk)
		{

		}

		float atk;
	};
}

#endif //_FLYINGPROPS_H
