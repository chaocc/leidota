#ifndef __WEAPON_YSG_CHOICE_AI_H__
#define __WEAPON_YSG_CHOICE_AI_H__

#include "WeaponYSGChoiceAI.h"

/**
*	石头人的武器选择
*/
class WeaponYSGChoiceAI : public WeaponChoiceAI
{
public:
    WeaponYSGChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner), m_normalProbability(0.9)
    {

    }

    virtual ~WeaponYSGChoiceAI()
    {

    }

protected:
    /**
    *	石头人也就只有
    *   （1）普通近距离攻击
    *   （2）石头雨
    *   暂时也是使用概率吧
    */
    virtual void choiceWeapon() override
    {
        // 暂时石头人也只有普通攻击
        changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
        return;

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
    const float m_normalProbability;                // 普通攻击的概率
};

#endif