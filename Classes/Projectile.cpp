#include "Projectile.h"
#include "ProjectileMonomerAttack.h"
#include "GameMap.h"
#include "ProjectileManager.h"
#include "ProjectileTrackMovingPart.h"
#include "ProjectileTypeOneShapePart.h"

int Projectile::m_count =   -1;

Projectile* Projectile::create( GameCharacterAttribute& att, ProjectileTypeEnum type, void* extraInfo )
{
    Projectile* pRet    =   nullptr;

    /**
    *	�����Ǹ����ӵ�����ͨ������װ���ķ�ʽ������Ҫ�Ƿ��ֲ��ü̳еķ�ʽ�����
    *   ���ֵ��۵�����
    */
    switch (type)
    {
    case PROJECTILE_TYPE_GALAXO_BALL:               // ������
        {
            // ���幥����
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            // @_@ װ���ƶ�����
            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1800);

            // @_@ װ����ʾ����
            pRet->setShapePart(new ProjectileTypeOneShapePart("xuejingling-texiao.ExportJson", 
                "xuejingling-texiao", "atk"));

            break;
        }

    default:
        break;
    }

    if (pRet != nullptr)
    {
        pRet->m_projectileType  =   type;
        pRet->autorelease();

        // ע�ᵽ��������
        ProjectileMgr->addProjectile(pRet);

        // ��ӵ���ͼ��
        GameMap::instance()->addProjectile(pRet);

        // ��ʼ����ı���
        pRet->getShapePart()->onLaunchStart();
    }
    return pRet;
}

Projectile::Projectile( GameCharacterAttribute& att )
{
    m_senderAtt     =   att;
    m_state         =   PROJECTILE_STATE_UPDATE | PROJECTILE_STATE_UPDATEMOVEMENT;
    m_projectileId  =   ++m_count;
}

Projectile::~Projectile()
{
    CC_SAFE_DELETE(m_movingPart);
    if (m_shapePart->getParent() != nullptr)
    {
        m_shapePart->removeFromParent();
    }
    CC_SAFE_DELETE(m_shapePart);
}

void Projectile::updateMovement( float dm )
{
    // ʹ���ƽ������µ�ǰ������
    m_movingPart->updateMovement(dm);
    m_shapePart->setPosition(m_movingPart->getPosition());
}
