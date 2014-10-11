#ifndef __WEAPON_SPIRIT_CHOICE_AI_H__
#define __WEAPON_SPIRIT_CHOICE_AI_H__

#include "WeaponChoiceAI.h"

/**
*	 ѩ���������ѡ��
*/
class WeaponSpiritChoiceAI : public WeaponChoiceAI
{
public:
    WeaponSpiritChoiceAI(GameCharacter* owner): WeaponChoiceAI(owner)
    {

    }

    virtual void changeTarget()
    {
        m_attackCount   =   0;
    }

    virtual void attack() override
    {
        if (m_pOwner->getWeaponControlSystem()->getCurrentWeaponType() == NORMAL_LONG_RANGE_WEAPON )
        {
            m_attackCount++;
        }
        else
        {
            m_attackCount   =   0;
        }

        WeaponChoiceAI::attack();
    }

protected:
    /**
    *	ѩ����ӵ��3�ֹ�����ʽ����ͨԶ�̹���������������ѩ������������600��ʱ��
    *   ʹ�ñ���ѩ����������ʱ����3����ͨ1�α�����ѡ��
    */
    virtual void choiceWeapon() override
    {
        if (m_pOwner->getAttribute().getEnergy() == 600)
        {
            changeWeapon(SPIRIT_SNOWSTORM_SKILL_WEAPON);
        }
        else
        {
            if (m_attackCount <= 3)
            {
                changeWeapon(NORMAL_LONG_RANGE_WEAPON);
            }
            else
            {
                changeWeapon(SPIRIT_FREEZE_SKILL_WEAPON);
            }
        }
    }

private:
    int m_attackCount;                      // ͳ����ͨԶ���빥���Ĵ���
};

#endif