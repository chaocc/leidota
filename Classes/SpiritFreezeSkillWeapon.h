#ifndef __SPIRIT_FREEZE_SKILL_WEAPON_H__
#define __SPIRIT_FREEZE_SKILL_WEAPON_H__

#include "Weapon.h"
#include "GameCharacterState.h"

/**
*	ѩ����ı���ħ�����øü��ܹ������ֿ����ڶ������ϲ�������Ч�����ö���
*   ���붳��״̬����ʱ��
*/
class SpiritFreezeSkillWeapon : public Weapon
{
public:
    SpiritFreezeSkillWeapon(GameCharacter* owner);
    virtual ~SpiritFreezeSkillWeapon();

    virtual void attack(GameCharacter* target) override
    {
        /**
        *	 @_@ ���𹥻�����ʵ�����õ��˽��붳��״̬����ʾ��һ����ʱҲ����
        *   ״̬���棬�Ժ���ܻ���ʹ����Ϣ�ķ�ʽ������Ŀǰͼ�򵥣���ֱ���޸�
        *   Ŀ���״̬
        */
        target->getFSM()->changeState(GameCharacterFrozenState::create());
        
        // @_@ Ӧ�û�������˺���������ʱ���Ų�д
    }

    virtual bool isInAttackRange(GameCharacter* target) override
    {
        // ��ʱд
        return true;
    }

    virtual bool isReadyForNextAttack() override
    {
        // @_@ ��ʱд
        return true;
    }

    virtual bool isAttacking()
    {
        return true;
    }
};

#endif