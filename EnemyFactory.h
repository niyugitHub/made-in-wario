#pragma once
#include "EnemyBase.h"
#include<list>
#include <memory>
#include "Vec2.h"

class Enemy1;
class Enemy2;
class Enemy3;
class Enemy4;
class Enemy5;
class BossEnemy;
class Player;
class Particle;
class Map;
class Collision;

class EnemyFactory
{
public:
	enum EnemyType
	{
		kNormal,
		kFly,
		kThrow,
		kJump,
		kFlyShot,
		kBoss,
	};
public:
	EnemyFactory();
	~EnemyFactory();

	void setCategory(char EnemyName) { m_EnemyName = EnemyName; }

	Vec2 GetPos() { return m_Pos; }
	void SetPos(Vec2 Pos) { m_Pos = Pos; }

	Vec2 GetThrowPos() { return m_ThrowPos; }

	Vec2 GetCentorPos() { return m_CentorPos; }

	// �G�l�~�[�̃T�C�Y�擾
	Vec2 GetGraphSize1() { return m_EnemySize1; } // ������W
	Vec2 GetGraphSize2() { return m_EnemySize2; }//  �E����W

	void SetPlayer(std::shared_ptr<Player> player) { m_Player = player; }
	void SetMap(std::shared_ptr<Map> map) { m_Map = map; }
	void SetColl(std::shared_ptr<Collision> Coll) { m_Coll = Coll; }

	void Init();
	void end();

	void Update();
	void Draw(Vec2 offset);

	std::shared_ptr<EnemyBase> Create(EnemyType type, const Vec2 pos);

	void AttackDamage();

	// �X�e�[�W���Ƃɓx�̃G�l�~�[���o�������邩
	void StageEnemy(int StageNum);

	// �G�l�~�[�����񂾂Ƃ��̏���(�X�e�[�W���ς�����Ƃ�)
	void EnemyDead();

private:
	int m_EnemyName;
	int m_Frame;

	// �G�l�~�[�̉摜�n���h��
	int m_handle;

	// �T�E���h�̃n���h��
	int m_SoundDamage = -1;
	int m_SoundHitAttack = -1;

	// �V���b�g�̉摜�n���h��
	int m_Shothandle;

	bool m_CollTop;
	bool m_CollBottom;
	bool m_CollRight;
	bool m_CollLeft;

	//// ���݊m�F
	//bool m_Exist;

	Vec2 m_Pos;

	// �G�l�~�[�̐^�񒆂̍��W
	Vec2 m_CentorPos = { 0,0 };

	// �G�l�~�[�̃T�C�Y�擾
	Vec2 m_EnemySize1;
	Vec2 m_EnemySize2;

	Vec2 m_ThrowPos;

	std::list<std::shared_ptr<EnemyBase>> m_Enemy;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Collision> m_Coll;
	std::shared_ptr<Particle> m_Particle;
};

