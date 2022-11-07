#pragma once
#ifndef __UNIT__H__
#define __UNIT__H__

#include "stdafx.h"


class Unit :public Node {
private:
	DrawNode* dn;
protected:
	Sprite* spr;
public:
	static Unit* create(const Size& size, int bitmask, int tag); // Size는 충돌판정 크기
	virtual bool init(const Size& size, int bitmask, int tag);
};
#endif // !__UNIT__H__
