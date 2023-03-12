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
	static Unit* create(const Size& size, int bitmask, int tag);//유닛 size를 기준으로 충돌 판정
	virtual bool init(const Size& size, int bitmask, int tag);

};
#endif // !__UNIT_H__
