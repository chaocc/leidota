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
    // �ж��Ƿ񵽴�
    if (canUpdateMovement())
    {
        float tmpDistance    =   
            (m_movingPart->getPosition() - m_movingPart->getTargetPos()).getLengthSq();
        if (tmpDistance <= 400)
        {
            // ��ֹ����λ��
            updateMovementOff();
            // ˵�������������Ѿ���λ����ʼ�������Ŷ���
            m_shapePart->onImpact();

            // ������Ϣ���ܻ��ߣ�@_@������idû�б�Ҫ
            auto tmpMsg = TelegramNormalAttack::create(0, m_targetId, m_senderAtt);
            Dispatch->dispatchMessage(*tmpMsg);
        }
    }
    else
    {
        // ������������Ϻ��
        if (m_shapePart->canBeDestroy())
        {
            updateOff();
        }
    }
}