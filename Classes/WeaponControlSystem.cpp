#include "WeaponControlSystem.h"
#include "NormalCloseRangeWeapon.h"
#include "GameCharacter.h"
#include "GameTeam.h"
#include "EntityManager.h"
#include "WeaponChoiceAI.h"

WeaponControlSystem::WeaponControlSystem( GameCharacter* owner ):m_updateInterval(1)
{
    m_pOwner            =   owner;
    m_currentWeapon     =   nullptr;
    m_updateCountTime   =   0;
    m_targetId          =   INVALID_GAME_ENTITY_ID;
}

WeaponControlSystem::~WeaponControlSystem()
{
    for (auto tmpIterator = m_allWeapons.begin(); tmpIterator != m_allWeapons.end(); tmpIterator++)
    {
        delete tmpIterator->second;
    }

    m_allWeapons.clear();

    // 武器选择AI部分
    CC_SAFE_DELETE(m_weaponChoiceAI);
}

void WeaponControlSystem::addWeapon(Weapon* aWeapon)
{
    // 添加到m_allWeapons中
    m_allWeapons.insert(WeaponMap::value_type(aWeapon->getWeaponType(), aWeapon));

    // @_@ 当前先这样写
    m_currentWeapon     =   aWeapon;
}

void WeaponControlSystem::takeWeaponAndAttack( GameCharacter* target )
{
    // 使用当前的武器攻击敌人
    if (m_currentWeapon->isInAttackRange(target) && m_currentWeapon->isReadyForNextAttack())
    {
        // 面向敌人
        if (m_pOwner->getMovingEntity().getPosition().x > target->getMovingEntity().getPosition().x)
        {
            m_pOwner->getShape()->faceToLeft();
        }
        else
        {
            m_pOwner->getShape()->faceToRight();
        }

        m_currentWeapon->attack(target);
        m_targetId  =   target->getId();
    }
}

bool WeaponControlSystem::isInAttackRange( GameCharacter* target )
{
    return m_currentWeapon->isInAttackRange(target);
}

bool WeaponControlSystem::canCharacterMove()
{
    // 只有当前武器不在攻击或者当前目标存在并且在攻击范围内
    auto tmpTarget  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return !m_currentWeapon->isAttacking() && !(tmpTarget != nullptr && isInAttackRange(tmpTarget));
}

void WeaponControlSystem::update(float dm)
{
    // 现在把这部分更新当前选择武器的逻辑交给外部对象
    m_weaponChoiceAI->update(dm);
}

bool WeaponControlSystem::changeWeapon( WeaponTypeEnum type )
{
    auto tmpIterator    =   m_allWeapons.find(type);
    if (tmpIterator == m_allWeapons.end())
    {
        return false;
    }
    else
    {
        m_currentWeapon =   tmpIterator->second;
        return true;
    }
}
