#ifndef __WEAPON_CONTROL_SYSTEM_H__
#define __WEAPON_CONTROL_SYSTEM_H__

#include <map>
#include "Weapon.h"

using namespace std;

class GameCharacter;
class WeaponChoiceAI;

/**
* 武器控制系统，这里负责维护角色身上的所有攻击方式，包括普通攻击、技能攻击等，包括
* 使用哪种方式来攻击的逻辑也在这里，关于攻击方式应该是要根据某些环境来得出使用某种
* 武器来攻击
*/
class WeaponControlSystem
{
public:
    WeaponControlSystem(GameCharacter* owner);
    ~WeaponControlSystem();

    /**
    * 给该武器系统添加武器类型 
    */
    void addWeapon(Weapon* aWeapon);

    /**
    *	定时在主循环中被调用，在这里会根据当前的情况选择合适的武器来发起
    *   当前的攻击
    */
    void update(float dm);

    /**
    * 使用当前武器并且攻击某个目标 
    */
    void takeWeaponAndAttack(GameCharacter* target);

    /**
    * 返回使用当前武器的情况下，target是否在攻击范围内
    */
    bool isInAttackRange(GameCharacter* target);

    /**
    * @_@ 主要是因为在武器系统攻击的时候，角色是不能更新位置的，所以
    */
    bool canCharacterMove();

    /**
    *	 设置武器选择的AI部分
    */
    void setWeaponChoiceAI(WeaponChoiceAI* aAI) { m_weaponChoiceAI = aAI; }

    /**
    *	更换武器，如果更换成功就返回true，否则返回false 
    */
    bool changeWeapon(WeaponTypeEnum type);

private:
    GameCharacter*                              m_pOwner;           // 当前武器拥有者

    Weapon*                                     m_currentWeapon;    // 当前武器

    WeaponChoiceAI*                             m_weaponChoiceAI;   // 武器选择AI
    
    typedef map<WeaponTypeEnum, Weapon*> WeaponMap;
    WeaponMap        m_allWeapons;                                  // 当前角色拥有的所有武器

    int                                         m_targetId;         // 临时记录上一次攻击的目标的id

    const float m_updateInterval;                                   // 这个应该没有必要每次都更新
    float m_updateCountTime;                                        // 更新的计数时间
};

#endif