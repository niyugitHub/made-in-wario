#pragma once
#include "vec2.h"
class Particle
{
public:
	//�p�[�e�B�N���̍ő��
	static constexpr int kMaxParticle = 500;
public:
	Particle();
	~Particle();

	// �v���C���[�̍��W�擾
	void SetPos(Vec2 Pos);

	//�G�l�~�[�̍��W�擾
	void SetEnemyPos(Vec2 EnemyPos);

	void Init();

	// �^�C�g���ŏo���p�[�e�B�N��
	void SetTitleParticle();
	// �v���C���[�񕜎��p�[�e�B�N��
	void SetPlayerParticle();
	// �v���C���[���V���b�g��ł������̃p�[�e�B�N��
	void SetShotPlayerParticle();
	// �v���C���[���U�����ꂽ�Ƃ��p�[�e�B�N��
	void SetdamagePlayerParticle();
	// �G�l�~�[�ɍU���q�b�g���p�[�e�B�N��
	void SetEnemyParticle();

	void Update();

	// �p�[�e�B�N������ʊO�ɏo���Ƃ�
	bool OffScreen(int i);


	void Draw(Vec2 offset);

	void TitleDraw();

private:
	struct Data
	{
		// �p�[�e�B�N���̍��W
		Vec2 m_Pos = {0,0};
		// �p�[�e�B�N���̓���
		Vec2 m_Vec = { 0,0 };
		// �F���Ƃ̔Z��
		int m_RColor = 0;
		int m_GColor = 0;
		int m_BColor = 0;
		// �����x
		int m_Transparency = 0;
		// ���݂��邩�ǂ���
		bool m_Exist = false;

		// �p�[�e�B�N���̃T�C�Y
		Vec2 m_ParticleSize = { 0,0 };
	};

	int m_Frame;

	Data data[kMaxParticle];

	// �d��
	float m_Gravity;
};

