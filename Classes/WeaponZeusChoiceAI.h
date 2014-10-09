#ifndef __WEAPON_ZEUS_CHOICE_AI_H__
#define __WEAPON_ZEUS_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 ��˹������ѡ��
*/
class WeaponZeusChoiceAI : public WeaponChoiceAI
{
public:
    WeaponZeusChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner), m_thumpProbability(0.2)
    {

    }

    virtual ~WeaponZeusChoiceAI()
    {

    }

protected:
    /**
    *	 ��˹ӵ��3�ֹ�����ʽ
    *   ��1����ͨ�����빥��
    *   ��2������ͷ����ͨԶ���빥����
    *   ��3���ػ�
    *   ��ѡ��������Ҫ�ڣ�1����2���У�ż���ᱬ����3��
    */
    virtual void choiceWeapon() override
    {
        int tmpPosId            =   m_pOwner->getMovingEntity().getFormationPosId();
        WeaponTypeEnum tmpType  =   NORMAL_CLOSE_RANGE_WEAPON;
        if ( tmpPosId>= 0 && tmpPosId <= 2 )
        {
            tmpType =   choiceCloseAttOrThump();
        }
        else
        {
            auto tmpCharacter   =   m_pOwner->getTeam()->getMemberIdFromFormation(tmpPosId % 3);
            if (tmpCharacter != nullptr)
            {
                tmpType =   NORMAL_LONG_RANGE_WEAPON;
            }
            else
            {
                tmpType =   choiceCloseAttOrThump();
            }
        }

        changeWeapon(tmpType);
    }

private:
    /**
    *	���ݸ���ѡ������빥�������ػ� 
    */
    WeaponTypeEnum choiceCloseAttOrThump()
    {
        if (CCRANDOM_0_1() < m_thumpProbability)
        {
            return ZEUS_THUMP_SKILL_WEAPON;
        }
        else
        {
            return NORMAL_CLOSE_RANGE_WEAPON;
        }
    }

    const float m_thumpProbability;             // �ػ��ĸ���
};

#endif