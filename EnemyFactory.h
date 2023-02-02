#pragma once

class Enemy1;
class Enemy2;

class EnemyFactory
{
private:
	enum EnemyCategory
	{
		kNormal,
		kJump,
	};
public:
	EnemyFactory();
	~EnemyFactory();

	void setCategory(char EnemyName) { m_EnemyName = EnemyName; }

	void Init();
	void end();

	void Update();
	void Draw();

private:
	int m_EnemyName;
	Enemy1* m_NormalEnemy;
	Enemy2* m_JumpEnemy;
};

