#ifndef __ZEUS_THUMP_SKILL_WEAPON_H__
#define __ZEUS_THUMP_SKILL_WEAPON_H__

#include "NormalCloseRangeWeapon.h"

/**
*	 ��˹���ػ����ܣ�@_@ ��Ϊ���ֺ�������빥��������͵���������ڼ����Ȳ�����
*    �θĶ�
*/
class ZeusThumpSkillWeapon : public NormalCloseRangeWeapon
{
public:
    ZeusThumpSkillWeapon(GameCharacter* owner):NormalCloseRangeWeapon(owner, 3, "atk2")
    {
        // ��Ҫ�ֶ�����һ��
        m_weaponType    =  ZEUS_THUMP_SKILL_WEAPON; 
    }
};

#endif