#include "stdafx.h"
#include "EnemyComponent.h"
#include "SceneIngame.h"
#include "Bullet.h"

EnemyAttackRoutine* EnemyAttackRoutine::create(EnemyAttackType t)
{
    auto ret = new EnemyAttackRoutine();
    if (ret && ret->init(t)) ret->autorelease();
    else CC_SAFE_DELETE(ret);
    return ret;
}

bool EnemyAttackRoutine::init(EnemyAttackType t)
{
    if (!Component::init()) return false;

    this->type = t;

    return true;
}

void EnemyAttackRoutine::update(float dt)
{
    switch (this->type) {
    case EnemyAttackType::NORMAL: logic_normal(dt); break;

    }
}

void EnemyAttackRoutine::logic_normal(float dt)
{
    elapsed += dt;
    if (elapsed > 1.0f) //1초가 지나면
    {
        elapsed = 0.0f;
        SceneIngame* scene = (SceneIngame *)Director::getInstance()->getRunningScene(); //현재 실행중인 scene가져옴, 반환값 scene
        auto player = scene->getPlayer();

        if (player == nullptr) return;

        auto bullet = Bullet::create(ENEMY_BULLET_MASK, TAG_ENEMY_BULLET);
        bullet->setPosition(getOwner()->getPosition()); //총알이 적의 위치에 위치하도록
       
        //getOwner: Component class method; it retunrs a node contains component
        scene->addChild(bullet);

        Vec2 pos = player->getPosition() - getOwner()->getPosition(); //플레이어의 벡터 - owner의 벡터 = 플레이어와 적 사이 벡터값
        pos = pos.getNormalized() * ENEMY_BULLET_SPEED; // 길이가 1인 벡터로 변환(단위벡터로 변환, 방향을 나타냄)*투사체의 속도
        bullet->getBody()->setVelocity(pos);

        bullet->runAction(Sequence::create(
            DelayTime::create(1.0f),
            RemoveSelf::create(),
            nullptr
        ));
    }
}
