#ifndef __SPIRIT_FREEZE_SKILL_WEAPON_H__
#define __SPIRIT_FREEZE_SKILL_WEAPON_H__

#include "Weapon.h"
#include "GameCharacterState.h"

/**
*	雪精灵的冰冻魔法，用该技能攻击对手可以在对手身上产生冰冻效果，让对手
*   进入冻结状态若干时间
*/
class SpiritFreezeSkillWeapon : public Weapon
{
public:
    SpiritFreezeSkillWeapon(GameCharacter* owner);
    virtual ~SpiritFreezeSkillWeapon();

    virtual void attack(GameCharacter* target) override
    {
        /**
        *	 @_@ 发起攻击，其实就是让敌人进入冻结状态，显示这一块暂时也放在
        *   状态里面，以后可能还是使用消息的方式，但是目前图简单，先直接修改
        *   目标的状态
        */
        target->getFSM()->changeState(GameCharacterFrozenState::create());
        
        // @_@ 应该还会造成伤害，这里暂时留着不写
    }

    virtual bool isInAttackRange(GameCharacter* target) override
    {
        // 临时写
        return true;
    }

    virtual bool isReadyForNextAttack() override
    {
        // @_@ 临时写
        return true;
    }

    virtual bool isAttacking()
    {
        return true;
    }
};

#endif