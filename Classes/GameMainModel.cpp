#include "GameMainModel.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "ProjectileManager.h"
#include "TimeTool.h"

GameMainModel::GameMainModel()
{
    // ��ʼѭ��
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameMainModel::update, this), 
        this, GAMEMAINMODEL_LOOP_INTERVAL, false, GAMEMAINMODEL_SCHEDULE_KEY);
}

GameMainModel::~GameMainModel()
{

}

void GameMainModel::moveToLeft()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_MOVE_LEFT, 0));
    }
    
    CCLOG("moveToLeft");
}

void GameMainModel::moveToRight()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_MOVE_RIGHT, 0));
    }
    
    CCLOG("moveToRight");
}

void GameMainModel::idle()
{
/**
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_IDLE, 0));
    }

    CCLOG("idle");
*/
}

void GameMainModel::changeTarget()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        // ���������л�Ŀ��
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_CHANGE_TARGET, 0));
    }
}

void GameMainModel::update(float dm)
{
    // ��������Ϸ�߼����µ�������ģ�������Ϸ�߼���ʱ�䶼�����ڴ�
    // dm  *=  2;

    // ʱ��
    TimeTool::update(dm);

    // �����߼�����
    TeamMgr->update(dm);

    // �����еġ��ӵ�������
    ProjectileMgr->update(dm);
}

void GameMainModel::setMainGameCharacter(GameCharacter* character)
{
    EntityMgr->setmainEntity(character);
}