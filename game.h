#pragma once

namespace Game
{
#ifdef _DEBUG
	// �E�C���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// �E�C���h�E��
	const char* const kTitleText = "�Q�[����";
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1080;
	constexpr int kScreenHeight = 1080;
	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16
};