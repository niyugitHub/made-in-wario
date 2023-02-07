#pragma once
#include"Vec2.h"
#include<memory>

class Player;
class EnemyFactory;
class Map;

class Collision
{
public:
	Collision();

	~Collision();

	void setPlayer(std::shared_ptr<Player> pPlayer) { m_player = pPlayer; }
	void setMap(std::shared_ptr<Map> pMap) { m_Map = pMap; }
	void setEnemy(std::shared_ptr<EnemyFactory> pEnemy) { m_enemy = pEnemy; }

	// �v���C���[�ƃ}�b�v�̓����蔻��
	bool IsCollTop() { return m_CollTop; }
	bool IsCollBottom() { return m_CollBottom; }
	bool IsCollRight() { return m_CollRight; }
	bool IsCollLeft() { return m_CollLeft; }

	// �G�l�~�[�ƃ}�b�v�̓����蔻��
	bool IsCollTopEnemy() { return m_CollTopEnemy; }
	bool IsCollBottomEnemy() { return m_CollBottomEnemy; }
	bool IsCollRightEnemy() { return m_CollRightEnemy; }
	bool IsCollLeftEnemy() { return m_CollLeftEnemy; }


	void Update();

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	bool IsCollEnemy();

	// �v���C���[�̍U������
	bool IsCollAttackPlayer();

	// �v���C���[�ƃ}�b�v�̓����蔻��
	void IsCollMap();

	// �v���C���[�ƃ}�b�v�̓����蔻��
	void IsCollMapEnemy();

	void InitColl();

	bool FallPlayer();

	// �v���C���[�̏㉺���E�̍��W
	void PlayerDirectPos();

	// �G�l�~�[�̏㉺���E�̍��W
	void EnemyDirectPos();

	void MapInfo(int i,int j);

private:
	// �v���C���[�ƃ}�b�v�̓����蔻��
	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	// �G�l�~�[�ƃ}�b�v�̓����蔻��
	bool m_CollTopEnemy;
	bool m_CollBottomEnemy;
	bool m_CollRightEnemy;
	bool m_CollLeftEnemy;

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	bool m_CollEnemy;

	// �}�b�v�`�b�v�̓����蔻�肪�������ɂ���Ƃ�
	bool m_CollSingle;

	// �}�b�v�`�b�v�ɓ����蔻�肪�Ȃ��Ƃ�
	bool m_MapColl;

	Vec2 m_PlayerPos;

	Vec2 m_EnemyPos;

	Vec2 m_MapPos;

	std::shared_ptr<Player> m_player;
	std::shared_ptr<EnemyFactory> m_enemy;
	std::shared_ptr<Map> m_Map;
};
