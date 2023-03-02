#include "DxLib.h"

#include"Vec2.h"
#include"SceneManager.h"
#include"Player.h"
#include"game.h"

namespace
{
	// �E�C���h�E���[�h�ݒ�
	constexpr bool kWindouwMode = Game::kWindowMode;
	// �E�C���h�E��
	const char* const kTitleText = "�Q�[����";
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = Game::kScreenWidth;
	constexpr int kScreenHeight = Game::kScreenHeight;
	// �J���[���[�h
	constexpr int kColorDepth = 32;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(kWindouwMode);
	
	// �E�C���h�E���ݒ�
	SetMainWindowText("�Q�[����");
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(kScreenWidth, kScreenHeight, 32);
	if (DxLib_Init() == -1)	// DX���C�u��������������
	{
		return -1;		// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager scene;
	scene.init();
	/*Player player;
	player.Init();*/

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		SetMouseDispFlag(1);

		auto fps = GetFPS();// Frame Per Second

		scene.update();
		scene.draw();

		/*player.update();
		player.draw();*/

		DrawFormatString(10, 10, 0xffffff,"FPS=%2.2f", fps);
		// ����ʂƕ\��ʂ����ւ���
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	scene.end();
	/*player.end();*/

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}