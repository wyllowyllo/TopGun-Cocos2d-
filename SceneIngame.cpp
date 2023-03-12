#include "stdafx.h"
#include "SceneInGame.h"
#include "Bullet.h"
#include "Unit.h"
#include "EnemyComponent.h"

SceneInGame* SceneInGame::create()
{
	auto ret = new SceneInGame();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);

	return ret;
}

bool SceneInGame::init()
{
	if(!Scene::initWithPhysics()) return false; //물리효과 적용


	auto keybd = EventListenerKeyboard::create(); //키보드 리스너함수 생성

	keybd->onKeyPressed = std::bind(&SceneInGame::onKeyPressed, this, std::placeholders::_1, std::placeholders::_2);
	keybd->onKeyReleased = std::bind(&SceneInGame::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);

	auto contact = EventListenerPhysicsContact::create(); //충돌 리스너 생성
	contact->onContactBegin = std::bind(&SceneInGame::onContactBegin, this,std::placeholders::_1);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, this);

	schedule(CC_SCHEDULE_SELECTOR(SceneInGame::logic)); //스케쥴 등록(상태 업데이트 계속)
	return true;
}

void SceneInGame::onEnter()
{
	Scene::onEnter();

	auto world = getPhysicsWorld(); //물리 월드 생성
	world->setGravity(Vec2::ZERO);
	if(DEBUG_MODE)world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //디버깅할때 사용

	player = Unit::create(Size(75,75),PLAYER_MASK,TAG_PLAYER);
	player->setPosition(Vec2(1280 / 2, 720 / 2-200));


	addChild(player);

	auto enemy = Unit::create(Size(75, 75), ENEMY_MASK, TAG_ENEMY);
	enemy->setPosition(Vec2(1280 / 2, 720 / 2+200));
	enemy->addComponent(EnemyAttackRoutine::create(EnemyAttacktype::NORMAL));
	addChild(enemy);
}

Unit* SceneInGame::getPlayer()
{
	return player;
}

void SceneInGame::onKeyPressed(EventKeyboard::KeyCode c, Event* e)
{
	const bool value = true;
	switch (c) {
	case EventKeyboard::KeyCode::KEY_W: up = value; break;
	case EventKeyboard::KeyCode::KEY_S: down = value; break;
	case EventKeyboard::KeyCode::KEY_A: left = value; break;
	case EventKeyboard::KeyCode::KEY_D: right = value; break;
	case EventKeyboard::KeyCode::KEY_J: fire = value; break;
	}
}

void SceneInGame::onKeyReleased(EventKeyboard::KeyCode c, Event* e)
{
	const bool value = false;
	switch (c) {
	case EventKeyboard::KeyCode::KEY_W: up = value; break;
	case EventKeyboard::KeyCode::KEY_S: down = value; break;
	case EventKeyboard::KeyCode::KEY_A: left = value; break;
	case EventKeyboard::KeyCode::KEY_D: right = value; break;
	case EventKeyboard::KeyCode::KEY_J: fire = value; break;
	}
}

bool SceneInGame::onContactBegin(PhysicsContact& contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();

	Node* a = contact.getShapeA()->getBody()->getNode();  //충돌 시 충돌한 개체의 노드로 계산
	Node* b = contact.getShapeB()->getBody()->getNode();

	if (tagA == TAG_PLAYER_BULLET && tagB == TAG_ENEMY) {
		b->removeFromParent();
	}
	if (tagA == TAG_ENEMY && tagB == TAG_PLAYER_BULLET) {
		a->removeFromParent();
	}
	if (tagA == TAG_PLAYER && tagB == TAG_ENEMY) {
		a->removeFromParent();
	}
	if (tagA == TAG_ENEMY && tagB == TAG_PLAYER) {
		b->removeFromParent();
	}
	if (tagA == TAG_PLAYER && tagB == TAG_ENEMY_BULLET) {
		a->removeFromParent();
	}
	if (tagA == TAG_ENEMY_BULLET && tagB == TAG_PLAYER) {
		b->removeFromParent();
	}
	return true;
}

void SceneInGame::logic(float dt)
{
	if (!player) return; //플레이어가 없으면 로직 작동 x

	Vec2 pos = player->getPosition();

	if (up) pos += Vec2(0,dt*PLAYER_MOVEMENT_SPEED);
	if (down) pos -= Vec2(0, dt * PLAYER_MOVEMENT_SPEED);
	if (left) pos -= Vec2(dt*PLAYER_MOVEMENT_SPEED,0);
	if (right) pos += Vec2(dt * PLAYER_MOVEMENT_SPEED, 0);

	player->setPosition(pos);

	if (fire) {
		auto bullet = Bullet::create(PLAYER_BULLET_MASK, TAG_PLAYER_BULLET);
		bullet->setPosition(player->getPosition());
		bullet->getbody()->setVelocity(Vec2(0, 1000));
		bullet->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(),nullptr)); //일정 시간 지나면 총알 사라짐
		addChild(bullet);
	}
}
