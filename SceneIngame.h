#pragma once
#ifndef __SCENE_INGAME_H__
#define __SCENE_INGAME_H__


#include "stdafx.h"
#include "Unit.h"
#include "Environment.h"
class SceneInGame :public Scene {
private:
	Unit* player = nullptr;
	bool up = false, down = false, left = false, right = false;
	bool fire = false; //ÃÑ¾Ë
public:
	static SceneInGame* create();
	virtual bool init() override;
	virtual void onEnter() override;

	Unit* getPlayer();
	void onKeyPressed(EventKeyboard::KeyCode c, Event*e);
	void onKeyReleased(EventKeyboard::KeyCode c, Event*e);

	bool onContactBegin(PhysicsContact& contact);
	void logic(float dt);

};
#endif // !__SCENE_INGAME_H__
