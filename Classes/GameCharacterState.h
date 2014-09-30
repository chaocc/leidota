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
    }

protected:
    GameCharacterFrozenState()
    {
        // @_@ ������д�ɣ�����2����
        m_maxFrozenTime =   2;
        m_frozenTime    =   0;   
    }

private:
    /**
    *	��ʱ����һ���ڽ����״̬ǰ��ɫ��һЩ���ݣ������˳���״̬��ʱ��
    *   �ָ�����
    */
    float           m_maxSpeed;         // ����ǰ������ٶȣ��ڽ������Ϊ0
    float           m_frozenTime;       // �Ѿ�����ʱ��
    float           m_maxFrozenTime;    // ��󶳽�ʱ�䣬�ڽ������Զ��ⶳ
};

#endif