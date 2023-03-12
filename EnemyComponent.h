#pragma once
#ifndef __ENEMYCOMPONENT_H__
#define __ENEMYCOMPONENT_H__

#include "stdafx.h"

enum class EnemyAttacktype {
	NORMAL
};
class EnemyAttackRoutine :public Component {
private:
	EnemyAttacktype type;
	float elapsed = 0;
public:
	static EnemyAttackRoutine* create(EnemyAttacktype t);
	virtual bool init(EnemyAttacktype t);

	virtual void update(float dt); //시간 변화량
	void logic_normal(float dt);
};

class EnemyMovementRoutine :public Component {

};
#endif // !__ENEMYCOMPONENT_H__

