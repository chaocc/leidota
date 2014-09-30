#ifndef __WEAPON_H__
#define __WEAPON_H__

class GameCharacter;

/**
* ��������@_@��Ҳ��֪����ôȥ���࣬��ʱ�����������ְ� 
*/
enum WeaponTypeEnum
{
    NORMAL_CLOSE_RANGE_WEAPON,          // ��ͨ��ս
    NORMAL_LONG_RANGE_WEAPON,           // ��ͨԶ��
    SPIRIT_FREEZE_SKILL_WEAPON,         // ѩ����ı�������
};

/**
* �ڸ���Ϸ�н����ֹ�����ʽ��������ͨ�����빥����Զ���빥�������ܹ����ȣ��ӽ�ɫ���Ϸ������������Ϊ
* ���������������һ����ɫ�ж��ֹ�����ʽ�����൱�ڸý�ɫЯ���ж�����������ÿ�ֹ����ı��֡�Ч������
* ������װ�������У����������������Ļ���
*/
class Weapon
{
public:
    Weapon(GameCharacter* owner, WeaponTypeEnum type);
    virtual ~Weapon();

    /**
    * ������������ 
    */
    WeaponTypeEnum getWeaponType();

    /**
    * ʹ�ø���������ָ����Ŀ��
    */
    virtual void attack(GameCharacter* target) = 0;

    /**
    * ���Ŀ���Ƿ��ڸ������Ĺ�����Χ��
    */
    virtual bool isInAttackRange(GameCharacter* target) = 0;

    /**
    * ���������Ƿ����׼���ü�����һ�ι��������ܻ��и��ָ��������ƣ� 
    */
    virtual bool isReadyForNextAttack() = 0;

    /**
    * ��鵱ǰ�Ƿ����ڹ�����
    * @_@ ��Ҫ����Ϊÿ�������Ĺ���ʱ����ͬ�������ڹ���ʱ���ڵ�ʱ���ǲ������ƶ�
    */
    virtual bool isAttacking() = 0;

protected:
    GameCharacter*      m_pOwner;                          // ������ӵ����
    WeaponTypeEnum      m_weaponType;                      // ��������
};

#endif