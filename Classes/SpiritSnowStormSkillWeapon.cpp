#include "SpiritSnowStormSkillWeapon.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "EntityManager.h"
#include "Tornado.h"

SpiritSnowStormSkillWeapon::SpiritSnowStormSkillWeapon( GameCharacter* owner ) 
    :Weapon(owner, SPIRIT_SNOWSTORM_SKILL_WEAPON), m_actionName("atk2")
{
    m_attRadius         =   650;
    m_minAttInterval    =   5;
}

void SpiritSnowStormSkillWeapon::attack( GameCharacter* target )
{
    // 先播放动画
    m_pOwner->getShape()->playAction(m_actionName, false, 
        std::bind(&SpiritSnowStormSkillWeapon::onAttackEffect, this, std::placeholders::_1));
    // 最短攻击间隔时间的
    m_lastAttackTime        =   TimeTool::getSecondTime();
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttInterval;
    m_targetId              =   target->getId();
}

bool SpiritSnowStormSkillWeapon::isInAttackRange( GameCharacter* target )
{
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
}

bool SpiritSnowStormSkillWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}

bool SpiritSnowStormSkillWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
}

void SpiritSnowStormSkillWeapon::onAttackEffect( string evt )
{
    if (!isTargetAlive())
    {
        return;
    }

    // 在当前目标所在位置产生一个龙卷风，龙卷风产生后就会在固定位置对周围的角色
    // 产生影响
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    auto tmpTornado     =   Tornado::create(m_pOwner->getId());
    tmpTornado->setPosition(tmpCharacter->getShape()->getPosition());
    GamepMapSingleton->addChildToPlayerLayer(tmpTornado);
}

bool SpiritSnowStormSkillWeapon::isTargetAlive()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpCharacter != nullptr && tmpCharacter->isAlive();
}
