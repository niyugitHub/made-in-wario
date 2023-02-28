#pragma once
#include"Vec2.h"
#include<memory>
#include "ShotBase.h"

class Map;
class Player;
class Collision;
class FallShot;
class HomingShot;

class EnemyBase
{
public:
	static constexpr float kGravity = 0.05f;
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void SetMap(std::shared_ptr<Map> pMap) { m_Map = pMap; }
	virtual void SetPlayer(std::shared_ptr<Player> pPlayer) { m_Player = pPlayer; }
	virtual void SetColl(std::shared_ptr<Collision> Coll) { m_Coll = Coll; }

	virtual void SetCollTop(bool Top) { m_CollTop = Top; }
	virtual void SetCollBottom(bool Bottom) { m_CollBottom = Bottom; }
	virtual void SetCollRight(bool Right) { m_CollRight = Right; }
	virtual void SetCollLeft(bool Left) { m_CollLeft = Left; }

	virtual void SetPos(Vec2 Pos) { m_Pos = Pos; }

	// �O���t���Z�b�g
	virtual void SetHandle(int handle) { m_handle = handle; }

	// �V���b�g�̃O���t���Z�b�g
	virtual void SetShotHandle(int Shothandle) { m_Shothandle = Shothandle; }

	// �U�����q�b�g
	void SetHit(bool HitAttack) { m_HitAttack = HitAttack; }
	bool GetHit() { return m_HitAttack; }

	virtual void Init();
	virtual void end();

	// �G���W�擾
	virtual Vec2 GetPos() { return m_NextPos; }

	// �G�����������̍��W�擾
	virtual Vec2 GetThrowPos() { return m_ThrowPos; }

	// �O���t�̃T�C�Y�擾
	virtual Vec2 GetGraphSize() { return m_GraphSize; }

	virtual void update();
	virtual void draw(Vec2 offset);

	virtual void MoveEnemy();

	virtual void BasicMoveEnemy();

	virtual void InitKnockBack(); // �m�b�N�o�b�N�̃X�s�[�h��������

	virtual void KnockBack(); // �m�b�N�o�b�N����

	virtual void OnDamage(int damage); // �_���[�W���󂯂����̏���

	virtual bool CollThrow(); // �V���b�g�ƃv���C���[�̓����蔻��

	// �v���C���[���������V���b�g�ƃG�l�~�[�̓����蔻��
	virtual bool CollShotPlayer(); 

	// ���݊m�F
	bool isExist() const { return m_Exist; }
	void setExist(bool isExist) { m_Exist = isExist; }

protected:
	// ���݂̃G�l�~�[�̃|�W�V����
	Vec2 m_Pos;
	// �ړ���
	Vec2 m_Vec;

	// ���̃t���[���̃G�l�~�[�̃|�W�V����
	Vec2 m_NextPos;

	// �������̍��W
	Vec2 m_ThrowPos;

	// �v���C���[�̍��W
	Vec2 m_PlayerPos;

	// �v���C���[�ƃG�l�~�[�̍��W�̍�
	Vec2 m_DistancePos;

	// �G�l�~�[�̉摜�n���h��
	int m_handle;
	// �V���b�g�̉摜�n���h��
	int m_Shothandle;

	float m_Gravity;

	int m_Hp; // �G�̗̑�

	bool m_HitAttack; // �v���C���[�̍U�����q�b�g�����Ƃ�

	float m_KnockBackSpeed; // �m�b�N�o�b�N�̃X�s�[�h
	float m_MaxKnockBackSpeed; // �m�b�N�o�b�N���̍ő�X�s�[�h

	// �ǂɓ����������ɋt�����ɐi�ނ��߂̕ϐ�
	int m_MoveInverseDirection;

	// �X�N���[���̃X�s�[�h
	Vec2 m_MapVec;

	// ���S����
	bool m_Exist;

	// �G�l�~�[�̌���(-1:�� 1:�E)
	int m_LookEnemy;

	// �摜�̎��
	int m_GraphX;
	int m_GraphY;

	// �摜�̃O���t�T�C�Y�擾
	Vec2 m_GraphSize;

	// �G�l�~�[�ƃu���b�N�̏Փ˔���
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;
	ShotBase* m_Shot;
};

