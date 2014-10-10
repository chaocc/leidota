#ifndef __WEAPON_YSG_CHOICE_AI_H__
#define __WEAPON_YSG_CHOICE_AI_H__

#include "WeaponYSGChoiceAI.h"

/**
*	ʯͷ�˵�����ѡ��
*/
class WeaponYSGChoiceAI : public WeaponChoiceAI
{
public:
    WeaponYSGChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner), m_normalProbability(0.5)
    {

    }

    virtual ~WeaponYSGChoiceAI()
    {

    }

protected:
    /**
    *	ʯͷ��Ҳ��ֻ��
    *   ��1����ͨ�����빥��
    *   ��2��ʯͷ��
    *   ��ʱҲ��ʹ�ø��ʰ�
    */
    virtual void choiceWeapon() override
    {
        if (CCRANDOM_0_1() < m_normalProbability)
        {
            changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
        }
        else
        {
            changeWeapon(YSG_METEORIC_STREAM_SKILL_WEAPON);
        }
    }

private:
    const float m_normalProbability;                // ��ͨ�����ĸ���
};

#endif