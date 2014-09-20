#ifndef __GOAL_ATTACK_SPECIFIED_TARGET_H__
#define __GOAL_ATTACK_SPECIFIED_TARGET_H__

#include "GoalComposite.h"
#include "GameCharacter.h"

/**
* ����ĳһ��ָ����ɫ��Ŀ�꣬���Զ����ǰ����������Χ�ڣ���������������Ŀ��
* ����ʱ��Ŀ���Ϊcompleted������ʹ��ʲô������ʽ���Ϳ�����ϵͳ
*/
class GoalAttackSpecifiedTarget : public GoalComposite<GameCharacter>
{
public:
    GoalAttackSpecifiedTarget(GameCharacter* owner, int targetId);

protected:
    virtual void activate() override;
    virtual GoalStateEnum process() override;

private:
    // �жϹ���Ŀ���Ƿ񻹴��
    bool isTargetAlive();

    // �ж�Ŀ���Ƿ��ڹ�����Χ��
    bool isInAttackDistance();

private:
    int m_targetId;                     // ָ���Ĺ���Ŀ��
};

#endif