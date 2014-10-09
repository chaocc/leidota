#ifndef __WEAPON_SPIRIT_CHOICE_AI_H__
#define __WEAPON_SPIRIT_CHOICE_AI_H__

#include "WeaponChoiceAI.h"

/**
*	 雪精灵的武器选择
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
    *	雪精灵只有普通远程攻击、冰冻、暴风雪，暂时还是用概率来控制选择哪种武器@_@ 
    */
    virtual void choiceWeapon() override
    {
        changeWeapon(choiceBetweenThree());
    }

private:
    /**
    *	@_@ 都不知道该怎么取名字了，反正这个就是返回根据概率计算好的选择的武器 
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

    const float m_normalProbability;            // 普通远距离攻击概率
    const float m_freezeProbability;            // 冰冻攻击概率
};

#endif