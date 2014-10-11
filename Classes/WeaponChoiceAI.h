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
    WeaponChoiceAI(GameCharacter* owner)
    {
        m_pOwner            =   owner;
    }

    virtual ~WeaponChoiceAI()
    {

    }

    /**
    *	ÿһ�ε��ã�������ݵ�ǰ���ѡ��һ�����ʵ����� 
    */
    void update()
    {
        // ��������һ�¸����������߼�
        choiceWeapon();
    }

    /**
    *	��Ϊ����ʲô������֮ǰ�Ĺ����йأ�������ÿ�ι�����ʱ����Ҫ�ص��ú�������Щ
    *   ��ɫ������������ȥ���Ǹ÷���
    */
    virtual void attack()
    {
        update();
    }

    /**
    *	�������˵�ǰ����Ŀ���ʱ�򱻵��ã�������ܻ�Ӱ���ɫ����ѡ����߼�
    */
    virtual void changeTarget()
    {

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
};

#endif