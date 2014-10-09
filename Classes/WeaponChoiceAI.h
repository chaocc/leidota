#ifndef __WEAPON_CHOICE_AI_H__
#define __WEAPON_CHOICE_AI_H__

#include <assert.h>
#include "WeaponControlSystem.h"
#include "GameCharacter.h"

class Weapon;

/**
*	��Ҫ�ǿ��ǵ���ʱʹ��ʲô�������ڲ�ͬ�Ľ�ɫ���в�ͬ���߼��ģ����Խ�
*   ��һ���߼�������һ���������ÿһ�ֽ�ɫʵ��һ����������������ѡ��
*   �������߼�
*/
class WeaponChoiceAI
{
public:
    WeaponChoiceAI(GameCharacter* owner):m_updateInterval(4)
    {
        m_pOwner            =   owner;
        m_updateCountTime   =   0;
    }

    virtual ~WeaponChoiceAI()
    {

    }

    /**
    *	��ʱ�������Ե�ǰʹ�õ����������������統ǰʹ��Զ�̹����������ĳɽ��̹��� 
    */
    void update(float dm)
    {
        if (m_updateCountTime == 0)
        {
            // ��������һ�¸����������߼�
            choiceWeapon();
        }
        m_updateCountTime   +=  dm;
        if (m_updateCountTime > m_updateInterval)
        {
            m_updateCountTime   =   0;
        }
    }

protected:
    /**
    *	�ڴ˴���װ����������ѡ���߼� 
    */
    virtual void choiceWeapon() = 0;
    
    /**
    *	�ṩ�Ŀ�ݷ�����ѡ������ 
    */
    void changeWeapon(WeaponTypeEnum aType)
    {
        assert(m_pOwner->getWeaponControlSystem()->changeWeapon(aType));
    }

    GameCharacter*    m_pOwner;                // ��Ӧ����������ϵͳ

private:
    const float m_updateInterval;                       // ���Ӧ��û�б�Ҫÿ�ζ�����
    float m_updateCountTime;                            // ���µļ���ʱ��
};

#endif