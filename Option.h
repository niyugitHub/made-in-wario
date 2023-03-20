#pragma once
class Option
{
public:
	Option(int GuideHandle, int GuideStringHandle);
	~Option();

	// �I�v�V�������A�N�e�B�u���ǂ����m�F
	void SetActivgeOption(bool OptionScene) { m_OptionScene = OptionScene; }
	bool GetActiveOption() { return m_OptionScene; }

	bool GetGuide() { return m_Guide; }

	// �^�C�g����ʂ̃I�v�V�������ǂ���
	void SetTitleOption(bool TitleScene) { m_TitleScene = TitleScene; }

	// 

	// �摜���Z�b�g
	void SetHandle(int handle) { m_OptionHandle = handle; }

	bool GetGameEnd() { return m_GameEnd; }

	void Init();
	void Update();

	void Draw();

	void CursorMove();

private:
	void FirstUpdate();
	void GamePadUpdate();
	void EndUpdate();

	void OptionDraw();
	void GamepadDraw();
	void GameEndDraw();
private:
	// �摜�擾
	int m_OptionHandle = -1;
	int m_StringHandle = -1;
	int m_GamepadHandle = -1;
	int m_GameEndHandle = -1;
	// �K�C�h�̃n���h��
	int m_GuideHandle = -1;
	int m_GuideStringHandle = -1;

	// ���Ԗڂ̃V�[����I�񂾂�
	int m_SceneNum;

	// �J�[�\���ړ����ɂȂ߂炩�ɃJ�[�\���𓮂���
	int m_CursorMove = 0;

	// �����x
	int m_Color = 0;

	// �I�v�V�����V�[�����ғ����Ă���Ƃ�
	bool m_OptionScene;

	// �K�C�h�̕\���̗L��
	bool m_Guide;

	// �Q�[���I���t���O
	bool m_GameEnd = false;

	bool m_TitleScene = false;

	// �����Ȃ�Q�[���I���ɂȂ�Ȃ��悤��
	int m_GameCount = 0;

	//update���������o�֐��|�C���^
	void (Option::* m_func)();

	//draw���������o�֐��|�C���^
	void (Option::* m_drawfunc)();
};

