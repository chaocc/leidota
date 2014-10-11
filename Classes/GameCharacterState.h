#ifndef __GAME_CHARACTER_STATE_H__
#define __GAME_CHARACTER_STATE_H__

#include "GameCharacter.h"
#include "State.h"

/**
*	游戏角色处于自由状态，也就是平时的时候处于的状态
*/
class GameCharacterFreeState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override
    {

    }

    virtual void update(GameCharacter *owner, float dm) override
    {

    }

    virtual void onExit(GameCharacter *owner) override
    {

    }

    CREATE_FUNC(GameCharacterFreeState);
};

/**
*	角色处于被冰冻状态，角色一动不动的站在那里，并在固定的时间内
*   解冻
*/
class GameCharacterFrozenState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter *owner) override
    {
        // 限制角色最大速度为0来让角色无法移动
        m_maxSpeed      =   owner->getMovingEntity().getMaxSpeed();
        owner->getMovingEntity().setMaxSpeed(0);

        // 停止当前动画
        owner->getShape()->freezeAnimation();

        // @_@ 在角色身上放置一个冰块，暂时先放在这里吧
        ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
        m_iceCake   =   Armature::create("xuejingling_VFX");
        m_iceCake->setPosition(owner->getShape()->getCenterPosLocation());
        owner->getShape()->addChild(m_iceCake, 10);
        m_iceCake->getAnimation()->play("atk3");
    }

    virtual void update(GameCharacter *owner, float dm) override
    {
        m_frozenTime    +=  dm;
        if (m_frozenTime >= m_maxFrozenTime)
        {
            owner->getFSM()->changeState(GameCharacterFreeState::create());
        }
    }

    virtual void onExit(GameCharacter *owner) override
    {
        owner->getMovingEntity().setMaxSpeed(m_maxSpeed);

        owner->getShape()->unfreezeAnimation(true);

        m_iceCake->removeFromParent();
    }

    CREATE_FUNC(GameCharacterFrozenState);

protected:
    GameCharacterFrozenState()
    {
        // @_@ 先这样写吧，冻结2秒钟
        m_maxFrozenTime =   2;
        m_frozenTime    =   0;   
    }

    CC_SYNTHESIZE(float, m_maxFrozenTime, MaxFrozenTime);   // 最大冻结时间，在结束后自动解冻

private:
    /**
    *	临时保存一下在进入该状态前角色的一些数据，以在退出该状态的时候
    *   恢复过来
    */
    float           m_maxSpeed;         // 进入前的最大速度，在进入后会变为0
    float           m_frozenTime;       // 已经冻结时间

    Armature*       m_iceCake;          // 冰块
};

/**
*	角色处于受击状态 
*/
class GameCharacterHitedState : public State<GameCharacter>
{
protected:
    GameCharacterHitedState():m_actionName("hit")
    {

    }

public:
    virtual void onEnter(GameCharacter* owner) override
    {
        // 播放受击动画
        owner->getShape()->playAction(m_actionName, false);

        // 同时该角色呆滞
        owner->dullOn();
    }

    virtual void update(GameCharacter *owner, float dm) override
    {
        // 动画播放完毕后就退出
        if (owner->getShape()->getCurrentAnimationName() != m_actionName)
        {
            owner->getFSM()->changeState(GameCharacterFreeState::create());
        }
    }

    virtual void onExit(GameCharacter *owner) override
    {
        owner->dullOff();
    }

    CREATE_FUNC(GameCharacterHitedState);

private:
    const string m_actionName;
};

#endif