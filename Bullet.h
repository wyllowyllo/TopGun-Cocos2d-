#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "stdafx.h"

class Bullet :public Node {
private:
	PhysicsBody* body;
public:
	static Bullet* create(int bitmask, int tag); //bitmask눈 충돌 판정에 사용, tag는 누구의 총알인지 구분
	virtual bool init(int bitmask, int tag);

	PhysicsBody* getbody();
};
#endif // !__BULLET_H__
