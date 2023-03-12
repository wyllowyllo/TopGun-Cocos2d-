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

	if (elapsed > 1.0f) { //1초 경과시
		elapsed = 0.0f;

		SceneInGame* scene = (SceneInGame*)Director::getInstance()->getRunningScene(); //현재 돌아가는 scene 가져옴
		auto player = scene->getPlayer();

		auto bullet = Bullet::create(ENEMY_BULLET_MASK,TAG_ENEMY_BULLET);
		bullet->setPosition(getOwner()->getPosition()); //getOwner은 해당 컴포넌트를 가지고 있는 노드를 반환
		scene->addChild(bullet);

		Vec2 pos = player->getPosition();
		pos -= getOwner()->getPosition(); //플레이어 위치 방향벡터를 총알 방향으로 설정
		pos = pos.getNormalized() * ENEMY_BULLET_SPEED;//getNormalized->길이 1인 단위벡터로 변환
		bullet->getbody()->setVelocity(pos);

		bullet->runAction(Sequence::create(DelayTime::create(1.0), RemoveSelf::create(), nullptr));
	}
}
