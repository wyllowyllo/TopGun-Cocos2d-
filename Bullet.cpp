#include "stdafx.h"
#include "Bullet.h"

Bullet* Bullet::create(int bitmask, int tag)
{
	auto ret = new Bullet();

	if (ret && ret->init(bitmask, tag)) ret->autorelease();
	else CC_SAFE_DELETE(ret);

	return ret;
}

bool Bullet::init(int bitmask, int tag)
{
	if (!Node::init()) return false;

	body = PhysicsBody::createCircle(5.0f);
	body->setCollisionBitmask(0); //�Ѿ˳��� �浹 x
	body->setContactTestBitmask(bitmask); //�� body �浹 �� �浹 ������ ������
	body->setTag(tag);

	this->addComponent(body);
	return true;
}

PhysicsBody* Bullet::getbody()
{
	return this->body;
}
