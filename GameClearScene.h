#pragma once
#include<memory>

class Particle;

class GameClearScene
{
public:
	GameClearScene(int handle);
	~GameClearScene();

	void SetHandle(int i, int PlayerHandle) { m_PlayerHandle[i] = PlayerHandle; }

	bool GetPlayAgain() { return m_PlayAgain; }

	// �T�E���h���Z�b�g
	void SetSoundSelection(int handle) { m_SoundSelection = handle; }
	void SetSoundDetermination(int handle) { m_SoundDetermination = handle; }

	bool GetAbort() { return m_Abort; }

	void Init();
	void Update();
	void Draw();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
private:
	int m_handle = -1;

	int m_PlayerHandle[72];

	// �T�E���h�n���h��
	int m_SoundGameClear = -1;
	int m_SoundSelection = -1;
	int m_SoundDetermination = -1;

	// �O���t�̎��
	int m_Graph;
	// �O���t�̐؂�ւ��t���[��
	int m_GraphFrame;
	// �J�[�\���̏ꏊ
	int m_Cursor;
	// �J�[�\���ړ����ɂȂ߂炩�ɃJ�[�\���𓮂���
	int m_CursorMove = 0;

	// ������x�V�ԃt���O
	bool m_PlayAgain;
	// ��߂�t���O
	bool m_Abort;

	// �����x
	int m_Color = 0;

	//update���������o�֐��|�C���^
	void (GameClearScene::* m_func)();

	// �p�[�e�B�N��
	std::shared_ptr<Particle> m_Particle;
};

