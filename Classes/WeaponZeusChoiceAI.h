#ifndef __WEAPON_ZEUS_CHOICE_AI_H__
#define __WEAPON_ZEUS_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 宙斯的武器选择
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
    *	 宙斯拥有3种攻击方式
    *   （1）普通近距离攻击
    *   （2）丢斧头（普通远距离攻击）
    *   （3）重击
    *   他选择武器主要在（1）（2）中，偶尔会爆出（3）
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
    *	根据概率选择近距离攻击还是重击 
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

    const float m_thumpProbability;             // 重击的概率
};

#endif