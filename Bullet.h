#pragma once
#ifndef __BULLET__H
#define __BULLET__H

#include "stdafx.h"


class Bullet :public Node {
private:
	PhysicsBody* body;
public:
	static Bullet* create(int bitmask, int tag);
	bool init(int bitmask, int tag);
	PhysicsBody* getBody();
};
#endif // !__BULLET__H
