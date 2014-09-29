#include "ProjectileMonomerAttack.h"
#include "MathTool.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

ProjectileMonomerAttack::ProjectileMonomerAttack( GameCharacterAttribute& att, int targetId )
    :Projectile(att)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xuejingling-texiao.ExportJson");
    m_targetId  =   targetId;
    m_shapePart =   nullptr;
}

ProjectileMonomerAttack::~ProjectileMonomerAttack()
{
    
}

void ProjectileMonomerAttack::update( float dm )
{
    // 判断是否到达
    if (canUpdateMovement())
    {
        float tmpDistance    =   
            (m_movingPart->getPosition() - m_movingPart->getTargetPos()).getLengthSq();
        if (tmpDistance <= 400)
        {
            // 禁止更新位移
            updateMovementOff();
            // 说明此事闪电球已经到位，开始继续播放动画
            m_shapePart->onImpact();

            // 发送消息给受击者，@_@发送者id没有必要
            auto tmpMsg = TelegramNormalAttack::create(0, m_targetId, m_senderAtt);
            Dispatch->dispatchMessage(*tmpMsg);
        }
    }
    else
    {
        // 当动画播放完毕后就
        if (m_shapePart->canBeDestroy())
        {
            updateOff();
        }
    }
}