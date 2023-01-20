#pragma once
#include "game.h"

class Minigame1
{
	public:
		// �}�b�v�`�b�v�̂P�̃T�C�Y
		static constexpr int kChipSize = 64;

		// �`�b�v�̐�
		static constexpr int kBgNumY = 17;
		static constexpr int kBgNumX = 30;

	public:
		Minigame1();
		~Minigame1();

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
};

