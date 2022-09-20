#ifndef _SCENE_INGAME_H
#define _SCENE_INGAME_H

#include "stdafx.h"

class SceneIngame :public Scene {
private:
	Node* player;
	bool up = false, down=false , left=false, right=false;
	bool fire = false;
public:
	static SceneIngame* create();
	virtual bool init() override;
	virtual void onEnter() override;

	void onkeyPressed(EventKeyboard::KeyCode c, Event* e);
	void onkeyReleased(EventKeyboard::KeyCode c, Event* e);
	void logic(float dt);
};
#endif
