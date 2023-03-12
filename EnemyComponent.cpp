#include "stdafx.h"
#include "EnemyComponent.h"
#include "SceneInGame.h"
#include "Bullet.h"

EnemyAttackRoutine* EnemyAttackRoutine::create(EnemyAttacktype t)
{
	auto ret = new EnemyAttackRoutine;
	if (ret && ret->init(t)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool EnemyAttackRoutine::init(EnemyAttacktype t)
{
	if (!Component::init()) return false;
	this->type = EnemyAttacktype::NORMAL;
	return true;
}

void EnemyAttackRoutine::update(float dt)
{
	switch (this->type) {
	case EnemyAttacktype::NORMAL: logic_normal(dt); break;
	}
}

void EnemyAttackRoutine::logic_normal(float dt)
{
	elapsed += dt;

	if (elapsed > 1.0f) { //1�� �����
		elapsed = 0.0f;

		SceneInGame* scene = (SceneInGame*)Director::getInstance()->getRunningScene(); //���� ���ư��� scene ������
		auto player = scene->getPlayer();

		auto bullet = Bullet::create(ENEMY_BULLET_MASK,TAG_ENEMY_BULLET);
		bullet->setPosition(getOwner()->getPosition()); //getOwner�� �ش� ������Ʈ�� ������ �ִ� ��带 ��ȯ
		scene->addChild(bullet);

		Vec2 pos = player->getPosition();
		pos -= getOwner()->getPosition(); //�÷��̾� ��ġ ���⺤�͸� �Ѿ� �������� ����
		pos = pos.getNormalized() * ENEMY_BULLET_SPEED;//getNormalized->���� 1�� �������ͷ� ��ȯ
		bullet->getbody()->setVelocity(pos);

		bullet->runAction(Sequence::create(DelayTime::create(1.0), RemoveSelf::create(), nullptr));
	}
}
