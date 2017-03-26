#include "Item.h"

namespace ZS {
	Item::Item(std::string _name, int _id) :
		GameObject(_name, Tag::ITEM, Vec3::ZERO),
		id(_id) {
	}

	Item::~Item() {
	}
}
