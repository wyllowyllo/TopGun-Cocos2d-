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
	if(!Scene::initWithPhysics()) return false; //����ȿ�� ����


	auto keybd = EventListenerKeyboard::create(); //Ű���� �������Լ� ����

	keybd->onKeyPressed = std::bind(&SceneInGame::onKeyPressed, this, std::placeholders::_1, std::placeholders::_2);
	keybd->onKeyReleased = std::bind(&SceneInGame::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);

	auto contact = EventListenerPhysicsContact::create(); //�浹 ������ ����
	contact->onContactBegin = std::bind(&SceneInGame::onContactBegin, this,std::placeholders::_1);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, this);

	schedule(CC_SCHEDULE_SELECTOR(SceneInGame::logic)); //������ ���(���� ������Ʈ ���)
	return true;
}

void SceneInGame::onEnter()
{
	Scene::onEnter();

	auto world = getPhysicsWorld(); //���� ���� ����
	world->setGravity(Vec2::ZERO);
	if(DEBUG_MODE)world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //������Ҷ� ���

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

	Node* a = contact.getShapeA()->getBody()->getNode();  //�浹 �� �浹�� ��ü�� ���� ���
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
	if (!player) return; //�÷��̾ ������ ���� �۵� x

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
		bullet->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(),nullptr)); //���� �ð� ������ �Ѿ� �����
		addChild(bullet);
	}
}
