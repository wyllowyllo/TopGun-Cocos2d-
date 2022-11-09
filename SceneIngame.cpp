#include "stdafx.h"
#include "SceneIngame.h"
#include "Bullet.h"
#include "Unit.h"
#include "EnemyComponent.h"

SceneIngame* SceneIngame::create()
{
	auto ret = new SceneIngame();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneIngame::init()
{

	if (!Scene::initWithPhysics()) return false; // Create a Scene with physcis effect

	auto keybd = EventListenerKeyboard::create();
	keybd->onKeyPressed = std::bind(&SceneIngame::onkeyPressed, this, std::placeholders::_1, std::placeholders::_2);
	keybd->onKeyReleased = std::bind(&SceneIngame::onkeyReleased, this, std::placeholders::_1, std::placeholders::_2);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);
	schedule(CC_SCHEDULE_SELECTOR(SceneIngame::logic));

	auto contact = EventListenerPhysicsContact::create();
	contact->onContactBegin = std::bind(&SceneIngame::onContactBegin, this, std::placeholders::_1);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, this);
	return true;
}

void SceneIngame::onEnter()
{
	Scene::onEnter();
	auto world = getPhysicsWorld();
	world->setGravity(Vec2::ZERO);
	if(DEBUG_MODE )world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //only use when Debugging

	//player = Node::create();
	//player->setPosition(Vec2(1280 / 2, 720 / 2));


	//auto body = PhysicsBody::createBox(Size(75, 75)); // create a Box-shape component

	//body->setRotationEnable(false); // player doen't be rotated by object collision
	//body->setCollisionBitmask(0); //player doesn''t collide to bullets

	//player->addComponent(body); // Insert a Component to Ndoe. Componet makes a node do actions.
	//addChild(player);

	player = Unit::create(Size(75, 75), PLAYER_MASK, TAG_PLAYER);
	player->setPosition(Vec2(1280 / 2, 720 / 2));
	addChild(player);

	auto enemy = Unit::create(Size(75, 75), ENEMY_MASK, TAG_ENEMY);
	enemy->addComponent(EnemyAttackRoutine::create(EnemyAttackType::NORMAL));
	enemy->setPosition(Vec2(1280/2, 720/2+200));
	addChild(enemy);
}

Unit* SceneIngame::getPlayer()
{
	return this->player;
}

void SceneIngame::onkeyPressed(EventKeyboard::KeyCode c, Event* e)
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

void SceneIngame::onkeyReleased(EventKeyboard::KeyCode c, Event* e)
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

void SceneIngame::logic(float dt)
{
	if (!player) return;  // player==nullptr이면 종료

	Vec2 pos = player->getPosition();
	if (up) pos += Vec2(0, dt*PLAYER_MOVEMENT_SPEED);
	if (down) pos -= Vec2(0, dt * PLAYER_MOVEMENT_SPEED);
	if (left) pos -= Vec2(dt*PLAYER_MOVEMENT_SPEED, 0);
	if (right) pos += Vec2(dt * PLAYER_MOVEMENT_SPEED, 0);

	player->setPosition(pos);

	if (fire) {
		/*auto bullet = Node::create();
		auto body = PhysicsBody::createCircle(5);
		bullet->setPosition(player->getPosition());
		bullet->addComponent(body);
		body->setVelocity(Vec2(0, 1000));
		body->setCollisionBitmask(0);
		bullet->runAction(Sequence::create(
			DelayTime::create(1.0f),
			RemoveSelf::create(),
			nullptr
		));
		addChild(bullet);*/

		auto bullet = Bullet::create(PLAYER_BULLET_MASK,TAG_PLAYER_BULLET);
		bullet->setPosition(player->getPosition());
		bullet->getBody()->setVelocity(Vec2(0, 1000));
		bullet->runAction(Sequence::create(
			DelayTime::create(1.0f),
			RemoveSelf::create(),
			nullptr
		));
		addChild(bullet);
	}
}

bool SceneIngame::onContactBegin(PhysicsContact& contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	Node* a = contact.getShapeA()->getBody()->getNode(); // Unit은 Node를 상속받았으므로 Unit은 Node이다
	Node* b = contact.getShapeB()->getBody()->getNode();

	if (tagA == TAG_PLAYER_BULLET && tagB == TAG_ENEMY)
		b->removeFromParent();
	if (tagA == TAG_ENEMY && tagB == TAG_PLAYER_BULLET)
		a->removeFromParent();

	if (tagA == TAG_PLAYER && tagB == TAG_ENEMY) {
		a->removeFromParent();
		player = nullptr;
	}
	if (tagA == TAG_ENEMY && tagB == TAG_PLAYER) {
		b->removeFromParent();
		player = nullptr;
	}

	if (tagA == TAG_PLAYER && tagB == TAG_ENEMY_BULLET) {
		a->removeFromParent();
		player = nullptr;
	}
		
	if (tagB == TAG_ENEMY_BULLET && tagB == TAG_PLAYER) {
		b->removeFromParent();
		player = nullptr;
	}

	return true;
}
