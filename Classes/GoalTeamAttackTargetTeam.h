#ifndef __GOAL_TEAM_ATTACK_TARGET_TEAM_H__
#define __GOAL_TEAM_ATTACK_TARGET_TEAM_H__

#include "GoalComposite.h"
#include "GameTeam.h"

/**
*  ����ĸ߼�Ŀ��֮һ������Ŀ����飬����������̫Զ�����Զ����Ӷ��鼯��ǰ������Ŀ�꣬ͬʱ
*  �����Ŀ�괦�ڼ���״̬���ͻ᲻�ϵر����ö�������г�Ա�����θ���Щ��Ա������Ϣ�ƶ�Ŀ��
*/
class GoalTeamAttackTargetTeam : public GoalComposite<GameTeam>
{
public:
    GoalTeamAttackTargetTeam(GameTeam* owner, GameTeam* target);

protected:
    // @_@ ��ʱûɶ�õ�
    virtual void activate() override;
    
    // @_@ ��������Ҫ���ϵظ����ҷ���Ա���з���Ա������Լ���Ա������Ϣ
    virtual GoalStateEnum process() override;

private:
    // ���ÿһ����Ա��������Ҫ��ʱ������Ƿ�����Ϣ
    void inspectTeamMembers();

    GameTeam*       m_targetTeam;               // Ŀ�����
};

#endif