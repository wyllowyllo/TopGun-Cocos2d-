#pragma once
#ifndef __EnemyComponet__H__
#define __EnemyComponet__H__

#include"stdafx.h"


enum class EnemyAttackType {
	NORMAL
};
class EnemyAttackRoutine: public Component {
private:
	EnemyAttackType type;
	float elapsed=0;
public:
	static EnemyAttackRoutine* create(EnemyAttackType t);
	virtual bool init(EnemyAttackType t);

	virtual void update(float dt); //attack type update

	void logic_normal(float dt);  //bullet algorithm when the state is 'NORMAL'
};

class EnemyMoveRoutine : public Component {
private:

public:

};

#endif