#include "GameMap.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "cocostudio/CCSSceneReader.h"
#include "Projectile.h"

using namespace cocostudio;

GameMap* GameMap::m_instance    =   nullptr;
GameMap* GameMap::instance()
{
    if (m_instance == nullptr)
    {
        m_instance  =   new GameMap();
        m_instance->init();
    }

    return m_instance;
}

bool GameMap::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ���س����༭���༭�ĳ���
    auto tmpScene   =   SceneReader::getInstance()->createNodeWithSceneFile("leidota.json");
    this->addChild(tmpScene);

    // ��������
    m_bg3   =   tmpScene->getChildByTag(10013);
    // �����ɽ
    m_bg2   =   tmpScene->getChildByTag(10010);
    // �������ڵı���
    m_bg1   =   tmpScene->getChildByTag(10006);

    // �����ǽ
    m_walls.push_back(Wall2D(m_wallLBPos, Vec2(m_wallRTPos.x, 0), Vec2(0, 1)));
    m_walls.push_back(Wall2D(Vec2(m_wallRTPos.x, 0), m_wallRTPos, Vec2(-1, 0)));
    m_walls.push_back(Wall2D(m_wallRTPos, Vec2(0, m_wallRTPos.y), Vec2(0, -1)));
    m_walls.push_back(Wall2D(Vec2(0, m_wallRTPos.y), m_wallLBPos, Vec2(1, 0)));

    // @_@ ���еĽ�ɫ������ӵ��������
    m_playerLayer =   m_bg1->getChildByTag(10025);

    this->scheduleUpdate();

    return true;
}

GameMap::~GameMap()
{

}

void GameMap::cameraMove(int x)
{
    auto tmpTeam    =   TeamMgr->getTeamFromId(0);
    if (tmpTeam != nullptr)
    {
        // ������ǰ��������
        auto tmpCharacterPosX   =   tmpTeam->getTeamFormation().getFormationAnchor().x;
        auto visibleSize        = Director::getInstance()->getVisibleSize();
        float parentX           = visibleSize.width / 2 - tmpCharacterPosX;
        parentX    =    parentX > 0 ? 0 : parentX;
        m_bg1->setPositionX(parentX);

        // ����ɽ���ƶ��ٶ���һЩ
        m_bg2->setPositionX(parentX * MOUNTAIN_MOVE_SCALE);
        m_bg3->setPositionX(parentX * SKY_MOVE_SCALE);
    }
}

void GameMap::update( float x)
{
    cameraMove(0);

    // ͬʱ�����ڵ�ͼ��������н�ɫ��z
    auto tmpChildren    =   m_playerLayer->getChildren();
    for (auto tmpIterator = tmpChildren.begin(); tmpIterator != tmpChildren.end(); tmpIterator++)
    {
        (*tmpIterator)->setZOrder(500 - (*tmpIterator)->getPositionY());
    }
}

void GameMap::placeGameCharacter( GameCharacter* player )
{
    m_playerLayer->addChild(player->getShape());
}

void GameMap::addProjectile(Projectile* aProjectile)
{
    m_playerLayer->addChild(aProjectile->getShapePart());
}
