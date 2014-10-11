#ifndef __GAME_CHARACTER_STATE_H__
#define __GAME_CHARACTER_STATE_H__

#include "GameCharacter.h"
#include "State.h"

/**
*	��Ϸ��ɫ��������״̬��Ҳ����ƽʱ��ʱ���ڵ�״̬
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
*	��ɫ���ڱ�����״̬����ɫһ��������վ��������ڹ̶���ʱ����
*   �ⶳ
*/
class GameCharacterFrozenState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter *owner) override
    {
        // ���ƽ�ɫ����ٶ�Ϊ0���ý�ɫ�޷��ƶ�
        m_maxSpeed      =   owner->getMovingEntity().getMaxSpeed();
        owner->getMovingEntity().setMaxSpeed(0);

        // ֹͣ��ǰ����
        owner->getShape()->freezeAnimation();

        // @_@ �ڽ�ɫ���Ϸ���һ�����飬��ʱ�ȷ��������
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
        // @_@ ������д�ɣ�����2����
        m_maxFrozenTime =   2;
        m_frozenTime    =   0;   
    }

    CC_SYNTHESIZE(float, m_maxFrozenTime, MaxFrozenTime);   // ��󶳽�ʱ�䣬�ڽ������Զ��ⶳ

private:
    /**
    *	��ʱ����һ���ڽ����״̬ǰ��ɫ��һЩ���ݣ������˳���״̬��ʱ��
    *   �ָ�����
    */
    float           m_maxSpeed;         // ����ǰ������ٶȣ��ڽ������Ϊ0
    float           m_frozenTime;       // �Ѿ�����ʱ��

    Armature*       m_iceCake;          // ����
};

/**
*	��ɫ�����ܻ�״̬ 
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
        // �����ܻ�����
        owner->getShape()->playAction(m_actionName, false);

        // ͬʱ�ý�ɫ����
        owner->dullOn();
    }

    virtual void update(GameCharacter *owner, float dm) override
    {
        // ����������Ϻ���˳�
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