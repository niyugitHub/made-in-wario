#include"Vec2.h"
#include<memory>
#pragma once

class Map;
class Player;
class Collision;

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

	virtual void Init();
	virtual void end();

	virtual Vec2 GetPos() { return m_NextPos; }

	virtual void update();
	virtual void draw();

	virtual void MoveEnemy();

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

	// �v���C���[�̍��W
	Vec2 m_PlayerPos;

	// �v���C���[�ƃG�l�~�[�̍��W�̍�
	Vec2 m_DistancePos;

	float m_Gravity;

	// �ǂɓ����������ɋt�����ɐi�ނ��߂̕ϐ�
	int m_MoveInverseDirection;

	// �X�N���[���̃X�s�[�h
	Vec2 m_MapVec;

	// ���S����
	bool m_Exist;

	// �G�l�~�[�ƃu���b�N�̏Փ˔���
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollLeft;
	bool m_CollRight;

	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;

};

