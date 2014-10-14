#include "GoalCharacterThink.h"
#include "GoalAttackSpecifiedTarget.h"

GoalCharacterThink::GoalCharacterThink( GameCharacter* owner ):GoalComposite<GameCharacter>(owner)
{

}

GoalCharacterThink::~GoalCharacterThink()
{

}

GoalStateEnum GoalCharacterThink::process()
{
    return GoalComposite<GameCharacter>::process();
}

void GoalCharacterThink::activate()
{

}

/**
* �ҷ��ֶ�Ա�Ĵ����Ѿ�����˽��ܶ�����Ϣ�ĵط��ˣ�Ȼ����ݶ�����Ϣ�������Լ���Ŀ�� 
*/
bool GoalCharacterThink::handleMessage( Telegram& msg )
{
    // ���Ƚ�����Ŀ�괦��
    if (forwardMessageToFrontMostSubgoal(msg)) return true;

    switch (msg.type)
    {
    case TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD:                 // ����֪ͨ���¸������ǰ��
        {
            m_pOwner->getSteeringBehaviros()->keepFormationOn();
            return true;
        }

    case TELEGRAM_ENUM_TEAM_CANCEL_COLLECTIVE_FORWARD:          // ����֪ͨ���²��ø��������
        {
            m_pOwner->getSteeringBehaviros()->keepFormationOff();
            return true;
        }

    case TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET:            // �����������¹���ָ��Ŀ��
        {
            // ɾ�����еĵ�ǰ����Ȼ���趨�µ�����
            removeAllSubgoals();
            TelegramAttackSpecifiedTarget* pMsg =   dynamic_cast<TelegramAttackSpecifiedTarget*>(&msg);
            addSubgoal(new GoalAttackSpecifiedTarget(m_pOwner, pMsg->targetId, pMsg->targetTeamId));
            return true;
        }

    default:
        break;
    }

    return false;
}
