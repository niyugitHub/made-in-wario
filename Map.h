#pragma once
#include "game.h"
#include "Vec2.h"
#include<vector>
#include <memory>

class MapGimmick;

class Map
{
	public:
		// �}�b�v�`�b�v�̂P�̃T�C�Y
		static constexpr float kChipSize = 64;

		// �`�b�v�̐�
		static constexpr int kBgNumY[5] = { 20,17,17,17,17 };
		static constexpr int kBgNumX[5] = { 150,150,150,150,150 };

		// ���ʂɕ\���ł���}�b�v�`�b�v�̐�
		static constexpr int kChipNumY = 17;
		static constexpr int kChipNumX = 30;

		// �}�b�v�`�b�v������
		static constexpr int kChipDivisionX = 16;
		static constexpr int kChipDivisionY = 16;

		//	Platinum�ŕ������}�b�v�`�b�v�̉����̐�
		static constexpr int kSideMapChipNum = 16;

	public:
		Map();
		~Map();

	/*	void setPlayer(std::shared_ptr<Player> pPlayer) { m_player = pPlayer; }*/

		Vec2 GetPos() { return m_Pos; }
		Vec2 GetVec() { return m_ScrollSpeed; }

		int GetPosX() { return m_Pos.x; }

		// �M�~�b�N�̍��W�擾
		Vec2 GetGimmickPos(int i);
		// �M�~�b�N�̌��擾
		int GetGimmickCount() { return m_GimmickCount; }

		void SetMap(Vec2 Pos) { m_Pos = Pos; }

		// �X�e�[�W�̔ԍ����擾
		int GetStageNum() { return m_StageNum; }

		// �����蔻����Z�b�g
		void SetCollRight(bool Right) { m_CollRight = Right; }
		void SetCollLeft(bool Left) { m_CollLeft = Left; }

		// �}�b�v������
		void Init();

		// �O���t�B�b�N�̃��[�h�A�A�����[�h
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update();

		// �`��
		void draw(Vec2 offset);

		// �v���C���[�̌����ƃm�b�N�o�b�N�̈ړ���
		void PlayerMove(float knockback, float Move);

		// �}�b�v�̔ԍ��ύX
		void SetStage();

		// �L�����擾
		int getWidth() const;
		int getHeight() const;

		void SetPlayerPos(Vec2 PlayerPos) { m_PlayerPos = PlayerPos; }
	private:
		// �}�b�v�`�b�v�̐����擾����
		int chipNumX();
		int chipNumY();
		int chipNum();

	private:
		// �}�b�v�̕`��
		void drawMap(Vec2 offset);

		// �����蔻��
		bool m_CollLeft;
		bool m_CollRight;

		// �v���C���[�̍��W�擾
		Vec2 m_PlayerPos;

		// �w�i�̍��W�擾
		Vec2 m_BackGroundPos;

		// �O���t�B�b�N�f�[�^�̃n���h��
		int m_handle;
		// �M�~�b�N�̃n���h��
		int m_GimmickHandle;
		// �w�i�̃n���h��
		int m_BackGroundHandle[5];

		// �O���t�B�b�N�f�[�^�̔z��
		int m_MapData[50][500];

		// �X�e�[�W�ԍ�
		int m_StageNum;

		// �O���t�B�b�N�̃f�[�^
		int m_graphWidth;
		int m_graphHeight;

		//���[�̃}�b�v�̔ԍ�
		int m_LeftNum;

		//�E�[�̃}�b�v�̔ԍ�
		int m_RightNum;

		// �}�b�v�̍��[�̍��W
		Vec2 m_Pos;

		// �X�N���[���̃X�s�[�h
		Vec2 m_ScrollSpeed;

		// �x�N�g��
		Vec2 m_Vec;

		// �M�~�b�N�̌�
		int m_GimmickCount;

		// �M�~�b�N
		std::vector<std::shared_ptr<MapGimmick>> m_Gimmick;
};

