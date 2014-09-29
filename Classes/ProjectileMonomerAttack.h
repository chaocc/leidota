#ifndef __PROJECTILE_GALAXO_BALL_H__
#define __PROJECTILE_GALAXO_BALL_H__

#include "Projectile.h"

/**
*	���幥�����ӵ�
*/
class ProjectileMonomerAttack : public Projectile
{
public:
    ProjectileMonomerAttack(GameCharacterAttribute& att, int targetId);
    virtual ~ProjectileMonomerAttack();

    virtual void update(float dm) override;

private:
    int             m_targetId;     // ����Ŀ��
};

#endif