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

    // ����ѡ��AI����
    CC_SAFE_DELETE(m_weaponChoiceAI);
}

void WeaponControlSystem::addWeapon(Weapon* aWeapon)
{
    // ��ӵ�m_allWeapons��
    m_allWeapons.insert(WeaponMap::value_type(aWeapon->getWeaponType(), aWeapon));

    // @_@ ��ǰ������д
    m_currentWeapon     =   aWeapon;
}

void WeaponControlSystem::takeWeaponAndAttack( GameCharacter* target )
{
    // ʹ�õ�ǰ��������������
    if (m_currentWeapon->isInAttackRange(target) && m_currentWeapon->isReadyForNextAttack())
    {
        // �������
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
    // ֻ�е�ǰ�������ڹ������ߵ�ǰĿ����ڲ����ڹ�����Χ��
    auto tmpTarget  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return !m_currentWeapon->isAttacking() && !(tmpTarget != nullptr && isInAttackRange(tmpTarget));
}

void WeaponControlSystem::update(float dm)
{
    // ���ڰ��ⲿ�ָ��µ�ǰѡ���������߼������ⲿ����
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
