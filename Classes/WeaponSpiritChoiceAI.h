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
        ,m_normalProbability(0.1), m_freezeProbability(0.5)
    {

    }

protected:
    /**
    *	ѩ����ֻ����ͨԶ�̹���������������ѩ����ʱ�����ø���������ѡ����������@_@ 
    */
    virtual void choiceWeapon() override
    {
        changeWeapon(choiceBetweenThree());
    }

private:
    /**
    *	@_@ ����֪������ôȡ�����ˣ�����������Ƿ��ظ��ݸ��ʼ���õ�ѡ������� 
    */
    WeaponTypeEnum choiceBetweenThree()
    {
        auto tmpRandResult  =   CCRANDOM_0_1();
        if (tmpRandResult < m_normalProbability)
        {
            return NORMAL_LONG_RANGE_WEAPON;
        }
        else if (tmpRandResult < m_normalProbability + m_freezeProbability)
        {
            return SPIRIT_FREEZE_SKILL_WEAPON;
        }
        else
        {
            return SPIRIT_SNOWSTORM_SKILL_WEAPON;
        }
    }

    const float m_normalProbability;            // ��ͨԶ���빥������
    const float m_freezeProbability;            // ������������
};

#endif