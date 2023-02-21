#pragma once
#include "game.h"
#include "Vec2.h"
#include <memory>

class Map
{
	public:
		// �}�b�v�`�b�v�̂P�̃T�C�Y
		static constexpr int kChipSize = 64;

		// �`�b�v�̐�
		static constexpr int kBgNumY = 17;
		static constexpr int kBgNumX = 150;

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

		void SetMap(Vec2 Pos) { m_Pos = Pos; }

		// �X�e�[�W�̔ԍ����擾
		int GetStageNum() { return m_StageNum; }

		// �����蔻����Z�b�g
		void SetCollRight(bool Right) { m_CollRight = Right; }
		void SetCollLeft(bool Left) { m_CollLeft = Left; }

		// �O���t�B�b�N�̃��[�h�A�A�����[�h
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update(Vec2 offset);

		// �`��
		void draw();

		// �v���C���[�̌����ƃm�b�N�o�b�N�̈ړ���
		void PlayerMove(float knockback, float Move);

		// �}�b�v�̔ԍ��ύX
		void SetStage();

		// �L�����擾
		int getWidth() const;
		int getHeight() const;
	private:
		// �}�b�v�`�b�v�̐����擾����
		int chipNumX();
		int chipNumY();
		int chipNum();

	private:
		// �}�b�v�̕`��
		void drawMap();

		// �����蔻��
		bool m_CollLeft;
		bool m_CollRight;

		// �O���t�B�b�N�f�[�^�̃n���h��
		int m_handle;

		// �O���t�B�b�N�f�[�^�̔z��
		int m_MapData[kBgNumY][kBgNumX];

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
};

