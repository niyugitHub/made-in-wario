#pragma once
class GameOverScene
{
public:
	GameOverScene();
	~GameOverScene();

	/*void SetPlayAgain(bool GameOver) { m_PlayAgain = m_PlayAgain; }*/
	bool GetPlayAgain() { return m_PlayAgain; }

	/*void SetAbort(bool Abort) { m_Abort = Abort; }*/
	bool GetAbort() { return m_Abort; }

	// �Q�[���I�[�o�[�V�[�����A�N�e�B�u���ǂ����m�F
	void SetActivgeGameOver(bool ActiveGameOver) { m_ActiveGameOver = ActiveGameOver; }
	bool GetActiveGameOver() { return m_ActiveGameOver; }

	void Init();
	void Update();

	void Draw();

private:
	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();
private:
	// �摜�擾
	int m_Handle = -1;
	// ���Ԗڂ̃V�[����I�񂾂�
	int m_SceneNum;

	//// �J�[�\���̏ꏊ
	//int m_Cursor = 0;

	// �J�[�\���ړ����ɂȂ߂炩�ɃJ�[�\���𓮂���
	int m_CursorMove = 0;

	// ������x�V�ԃt���O
	bool m_PlayAgain;
	// ��߂�t���O
	bool m_Abort;

	// �����x
	int m_Color = 0;

	// �Q�[���I�[�o�[�V�[�����ғ����Ă���Ƃ�
	bool m_ActiveGameOver;

	//update���������o�֐��|�C���^
	void (GameOverScene::* m_func)();
};

