#pragma once
#include "game.h"
#include "Vec2.h"

class Map
{
	public:
		// �}�b�v�`�b�v�̂P�̃T�C�Y
		static constexpr int kChipSize = 64;

		// �`�b�v�̐�
		static constexpr int kBgNumY = 17;
		static constexpr int kBgNumX = 66;

		// ���ʂɕ\���ł���}�b�v�`�b�v�̐�
		static constexpr int kChipNumY = 17;
		static constexpr int kChipNumX = 30;

	public:
		Map();
		~Map();

		// �O���t�B�b�N�̃��[�h�A�A�����[�h
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update();

		// �`��
		void draw();
	private:
		// �}�b�v�`�b�v�̐����擾����
		int chipNumX();
		int chipNumY();
		int chipNum();

	private:
		// �}�b�v�̕`��
		void drawMap();

		// �O���t�B�b�N�f�[�^�̃n���h��
		int m_handle;

		// �O���t�B�b�N�f�[�^�̔z��
		int m_MapData[kBgNumY][kBgNumX];

		// �O���t�B�b�N�̃f�[�^
		int m_graphWidth;
		int m_graphHeight;

		//���[�̃}�b�v�̔ԍ�
		int m_LeftNum;

		//�E�[�̃}�b�v�̔ԍ�
		int m_RightNum;

		// �}�b�v�̍��[�̍��W
		Vec2 m_LeftPos;

		// �}�b�v�̉E�[�̍��W
		Vec2 m_RightPos;
};

