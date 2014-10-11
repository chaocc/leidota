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
    *	雪精灵拥有3种攻击方式，普通远程攻击、冰冻、暴风雪，当能量等于600的时候
    *   使用暴风雪，当不够的时候按照3次普通1次冰冻来选择
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
    int m_attackCount;                      // 统计普通远距离攻击的次数
};

#endif