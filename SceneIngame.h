#ifndef _SCENE_INGAME_H
#define _SCENE_INGAME_H

#include "stdafx.h"
#include "Unit.h"
// class Unit; ->클래스 전방선언


class SceneIngame :public Scene {
private:
	Unit* player=nullptr;
	bool up = false, down=false , left=false, right=false;
	bool fire = false;
public:
	static SceneIngame* create();
	virtual bool init() override;
	virtual void onEnter() override;

	Unit* getPlayer();
	void onkeyPressed(EventKeyboard::KeyCode c, Event* e);
	void onkeyReleased(EventKeyboard::KeyCode c, Event* e);
	void logic(float dt);
	bool onContactBegin(PhysicsContact& contact);
};
#endif
