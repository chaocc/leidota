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
    WeaponChoiceAI(GameCharacter* owner)
    {
        m_pOwner            =   owner;
    }

    virtual ~WeaponChoiceAI()
    {

    }

    /**
    *	每一次调用，都会根据当前情况选择一个合适的武器 
    */
    void update()
    {
        // 真正考虑一下更换武器的逻辑
        choiceWeapon();
    }

    /**
    *	因为是用什么武器与之前的攻击有关，所以在每次攻击的时候需要回调该函数，有些
    *   角色可以在子类中去覆盖该方法
    */
    virtual void attack()
    {
        update();
    }

    /**
    *	当更改了当前攻击目标的时候被调用，这个可能会影响角色武器选择的逻辑
    */
    virtual void changeTarget()
    {

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
};

#endif