#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "stdafx.h"

class Bullet :public Node {
private:
	PhysicsBody* body;
public:
	static Bullet* create(int bitmask, int tag); //bitmask�� �浹 ������ ���, tag�� ������ �Ѿ����� ����
	virtual bool init(int bitmask, int tag);

	PhysicsBody* getbody();
};
#endif // !__BULLET_H__
