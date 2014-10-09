#ifndef __WEAPON_CHOICE_AI_H__
#define __WEAPON_CHOICE_AI_H__

#include <assert.h>
#include "WeaponControlSystem.h"
#include "GameCharacter.h"

class Weapon;

/**
*	主要是考虑到何时使用什么武器对于不同的角色是有不同的逻辑的，所以将
*   这一块逻辑独立成一个对象，针对每一种角色实现一个子类来描述整个选择
*   武器的逻辑
*/
class WeaponChoiceAI
{
public:
    WeaponChoiceAI(GameCharacter* owner):m_updateInterval(4)
    {
        m_pOwner            =   owner;
        m_updateCountTime   =   0;
    }

    virtual ~WeaponChoiceAI()
    {

    }

    /**
    *	定时调用来对当前使用的武器做调整，比如当前使用远程攻击，后来改成进程攻击 
    */
    void update(float dm)
    {
        if (m_updateCountTime == 0)
        {
            // 真正考虑一下更换武器的逻辑
            choiceWeapon();
        }
        m_updateCountTime   +=  dm;
        if (m_updateCountTime > m_updateInterval)
        {
            m_updateCountTime   =   0;
        }
    }

protected:
    /**
    *	在此处封装真正的武器选择逻辑 
    */
    virtual void choiceWeapon() = 0;
    
    /**
    *	提供的快捷方法来选择武器 
    */
    void changeWeapon(WeaponTypeEnum aType)
    {
        assert(m_pOwner->getWeaponControlSystem()->changeWeapon(aType));
    }

    GameCharacter*    m_pOwner;                // 对应的武器控制系统

private:
    const float m_updateInterval;                       // 这个应该没有必要每次都更新
    float m_updateCountTime;                            // 更新的计数时间
};

#endif