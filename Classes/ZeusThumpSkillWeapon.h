#ifndef __ZEUS_THUMP_SKILL_WEAPON_H__
#define __ZEUS_THUMP_SKILL_WEAPON_H__

#include "NormalCloseRangeWeapon.h"

/**
*	 宙斯的重击技能，@_@ 因为表现很像近距离攻击，这里偷个懒，对于计算先不做任
*    何改动
*/
class ZeusThumpSkillWeapon : public NormalCloseRangeWeapon
{
public:
    ZeusThumpSkillWeapon(GameCharacter* owner):NormalCloseRangeWeapon(owner, 3, "atk2")
    {
        // 需要手动设置一下
        m_weaponType    =  ZEUS_THUMP_SKILL_WEAPON; 
    }
};

#endif