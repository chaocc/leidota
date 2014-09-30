#include "WeaponControlSystem.h"
#include "NormalCloseRangeWeapon.h"
#include "GameCharacter.h"
#include "GameTeam.h"
#include "EntityManager.h"

WeaponControlSystem::WeaponControlSystem( GameCharacter* owner ):m_updateInterval(1)
{
    m_pOwner            =   owner;
    m_currentWeapon     =   nullptr;
    m_updateCountTime   =   0;
}

WeaponControlSystem::~WeaponControlSystem()
{
    for (auto tmpIterator = m_allWeapons.begin(); tmpIterator != m_allWeapons.end(); tmpIterator++)
    {
        delete tmpIterator->second;
    }

    m_allWeapons.clear();
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
    m_updateCountTime   +=  dm;
    if (m_updateCountTime < m_updateInterval)
    {
        return;
    }
    else
    {
        m_updateCountTime   =   0;
    }

    // 先写一个最简单的规则
    int tmpPosId    =   m_pOwner->getMovingEntity().getFormationPosId();
    if ( tmpPosId>= 0 && tmpPosId <= 2 )
    {
        // 0~2位置编号的优先使用近程攻击能力，如果没有近程就使用远程
        if (!changeWeapon(NORMAL_CLOSE_RANGE_WEAPON))
        {
            changeWeapon(NORMAL_LONG_RANGE_WEAPON);
        }
    }
    else
    {
        auto tmpCharacter   =   m_pOwner->getTeam()->getMemberIdFromFormation(tmpPosId % 3);
        if (tmpCharacter != nullptr)
        {
            // 如果前面有人，优先远程
            if (!changeWeapon(NORMAL_LONG_RANGE_WEAPON))
            {
                changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
            }
        }
        else
        {
            if (!changeWeapon(NORMAL_CLOSE_RANGE_WEAPON))
            {
                changeWeapon(NORMAL_LONG_RANGE_WEAPON);
            }
        }
    }
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
