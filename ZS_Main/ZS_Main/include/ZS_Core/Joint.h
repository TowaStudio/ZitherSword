/**
 * Project ZS
 */


#ifndef _JOINT_H
#define _JOINT_H

#include "GameObject.h"

namespace ZS {
	class Joint : public GameObject {
	public:
		int id;
		Joint* next;
	};

}

#endif //_JOINT_H
