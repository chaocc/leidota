#ifndef __WEAPON_AER_CHOICE_AI_H__
#define __WEAPON_AER_CHOICE_AI_H__

#include "WeaponChoiceAI.h"

/**
*	 ��ʿѡ��������AI
*/
class WeaponAerChoiceAI : public WeaponChoiceAI
{
public:
    WeaponAerChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner), m_cryosphereProbability(0.5)
    {

    }

    virtual ~WeaponAerChoiceAI()
    {

    }

protected:
    /**
    *	 ��ʿֻ�����ֹ�����ʽ����ͨ�Ľ����빥���ͱ�Ȧ���������ǽ����빥������ǰ���߼�
    *    �����и��ʵ�ʹ�ñ�Ȧ����
    */
    virtual void choiceWeapon() override
    {
        changeWeapon(choiceCloseOrCryosphere());
    }

private:
    WeaponTypeEnum choiceCloseOrCryosphere()
    {
        if (CCRANDOM_0_1() < m_cryosphereProbability)
        {
            return AER_CRYOSPHERE_SKILL_WEAPON;
        }
        else
        {
            return NORMAL_CLOSE_RANGE_WEAPON;
        }
    }

    const float m_cryosphereProbability;            // ��Ȧ�ĸ���
};

#endif