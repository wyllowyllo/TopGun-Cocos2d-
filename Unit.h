#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#include "stdafx.h"
#include "Environment.h"


class Unit:public Node {
private:
	DrawNode* dn;
protected:
	Sprite* spr;
public:
	static Unit* create(const Size& size, int bitmask, int tag);//���� size�� �������� �浹 ����
	virtual bool init(const Size& size, int bitmask, int tag);

};
#endif // !__UNIT_H__
