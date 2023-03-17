#pragma once
#include<memory>

class Particle;

class GameClearScene
{
public:
	GameClearScene(int handle);
	~GameClearScene();

	bool GetPlayAgain() { return m_PlayAgain; }

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

