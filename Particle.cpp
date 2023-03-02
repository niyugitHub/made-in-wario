#include "Particle.h"
#include "Player.h"
#include"game.h"
#include <Dxlib.h>

namespace
{
	//パーティクルの重力
	constexpr float kGravity = 0.3f;
}

Particle::Particle() :
	m_Frame(0),
	m_Gravity(0)
{

	for (int i = 0; i < kMaxParticle; i++)
	{
		data[i].m_Pos = { 0,0 };
		data[i].m_Vec = { 0,0 };
		data[i].m_RColor = 0;
		data[i].m_GColor = 0;
		data[i].m_BColor = 0;
		data[i].m_Transparency = 0;
		data[i].m_Exist = false;
		data[i].m_ParticleSize = { 0,0 };
	}
}

Particle::~Particle()
{

}

void Particle::SetPos(Vec2 Pos)
{
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist)
		{
			/*Pos.x += -30 + GetRand(60);
			Pos.y += -30 + GetRand(60);*/
			data[i].m_Pos = Pos;

			/*float vecX = -1.5 + GetRand(3.0f);
			float vecY = -GetRand(5);

			data[i].m_Vec = { vecX,vecY };*/
		}
	}
}

void Particle::SetEnemyPos(Vec2 EnemyPos)
{
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist)
		{
			Vec2 Pos = { EnemyPos.x + 25, EnemyPos.y + 25 };

			data[i].m_Pos = Pos;
		}
	}
}

void Particle::Init()
{
}

void Particle::SetTitleParticle()
{
	if (m_Frame % 10 == 0)
	{
		for (int i = 0; i < kMaxParticle; i++)
		{
			if (!data[i].m_Exist)
			{
				data[i].m_Pos.x = GetRand(Game::kScreenWidth);
				data[i].m_Pos.y = Game::kScreenHeight;

				data[i].m_RColor = 255;
				data[i].m_GColor = 255;
				data[i].m_BColor = 200;
				data[i].m_Transparency = 5000;
				data[i].m_Exist = true;

				float vecX =  -0.5 + GetRand(1.0f);
				float vecY = -5 - GetRand(5.0f);
				m_Gravity = 0.0f;

				data[i].m_Vec = { vecX,vecY };

				float RandParticleSize = GetRand(10) + 5;

				data[i].m_ParticleSize = { RandParticleSize,RandParticleSize };

				return;
			}
		}
	}
}

void Particle::SetPlayerParticle()
{
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist/* && m_Frame % 2 == 0*/)
		{
			data[i].m_Pos.x += -30 + GetRand(60);
			data[i].m_Pos.y += -30 + GetRand(60);

			data[i].m_RColor = 255;
			data[i].m_GColor = 255;
			data[i].m_BColor = 255;
			data[i].m_Transparency = 255;
			data[i].m_Exist = true;

			float vecX = 0.0f;
			float vecY =  -2.5f - GetRand(2.5f);
			m_Gravity = 0.0f;

			data[i].m_Vec = { vecX,vecY };

			float ParticleSizeX = 3 + GetRand(4.0f);
			float ParticleSizeY = 7 + GetRand(6.0f);
			data[i].m_ParticleSize = { ParticleSizeX,ParticleSizeY };

			return;
		}
	}
}

void Particle::SetShotPlayerParticle()
{
	int count = 0;
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist)
		{
			/*data[i].m_Pos.x += Player::kSideSize / 2 - 10;
			data[i].m_Pos.y += Player::kColumnSize / 2 + 10;*/

			count++;
			data[i].m_RColor = 255;
			data[i].m_GColor = 255;
			data[i].m_BColor = 255;
			data[i].m_Transparency = 255;
			data[i].m_Exist = true;

			float FloatVec = 0.1 * count - 2.5f;

			float vecX = -5.0f + GetRand(10.0f) + FloatVec;
			float vecY = -2.5f - GetRand(5.0f) + FloatVec;

			data[i].m_Vec = { vecX, vecY };

			m_Gravity = 0.3f;

			data[i].m_ParticleSize = { 10,10 };

			if (count >= 50) return;
		}
	}
}

void Particle::SetdamagePlayerParticle()
{
	int count = 0;
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist)
		{
			data[i].m_Pos.x += Player::kSideSize / 2 - 20;
			data[i].m_Pos.y += Player::kColumnSize / 2;

			count++;
			data[i].m_RColor = 20;
			data[i].m_GColor = 20;
			data[i].m_BColor = 20;
			data[i].m_Transparency = 255;
			data[i].m_Exist = true;

			float FloatVec = 0.1 * count - 2.5f;

			float vecX = -5.0f + GetRand(10.0f) + FloatVec;
			float vecY = -2.5f - GetRand(5.0f) + FloatVec;

			data[i].m_Vec = { vecX, vecY };

			m_Gravity = 0.3f;

			/*float ParticleSizeX = 8 + GetRand(3.0f);
			float ParticleSizeY = 8 + GetRand(3.0f);
			data[i].m_ParticleSize = { ParticleSizeX,ParticleSizeY };*/

			data[i].m_ParticleSize = { 5,5 };

			if (count >= 50) return;
		}
	}
}

void Particle::SetEnemyParticle()
{
	int count = 0;
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (!data[i].m_Exist)
		{
			count++;
			data[i].m_RColor = 255;
			data[i].m_GColor = 128;
			data[i].m_BColor = 0;
			data[i].m_Transparency = 255;
			data[i].m_Exist = true;

			float FloatVec = 0.1 * count - 2.5f;

			float vecX = -5.0f + GetRand(10.0f) + FloatVec;
			float vecY = -2.5f - GetRand(5.0f) + FloatVec;

			data[i].m_Vec = { vecX, vecY };

			m_Gravity = 0.3f;

			data[i].m_ParticleSize = { 5,5 };

			if(count >= 50) return;
		}
	}
}

void Particle::Update()
{
	m_Frame++;
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (data[i].m_Exist)
		{
			//ブレンドをマイフレーム下げる
			data[i].m_Transparency -= 5;

			data[i].m_Pos.x += data[i].m_Vec.x;
			data[i].m_Pos.y += data[i].m_Vec.y;

			data[i].m_Vec.y += m_Gravity;

			if (data[i].m_Transparency < 0)
			{
				data[i].m_Exist = false;
			}
			if (OffScreen(i))
			{
				data[i].m_Exist = false;
			}
		}
	}
}

bool Particle::OffScreen(int i)
{
	if (data[i].m_Pos.x < 0)
	{
		return true;
	}
	if (data[i].m_Pos.x > Game::kScreenWidth)
	{
		return true;
	}
	if (data[i].m_Pos.y < 0)
	{
		return true;
	}
	if (data[i].m_Pos.y > Game::kScreenHeight)
	{
		return true;
	}

	return false;
}

void Particle::Draw(Vec2 offset)
{
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (data[i].m_Exist)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, data[i].m_Transparency);
			DrawOval(data[i].m_Pos.x + offset.x, data[i].m_Pos.y,
				data[i].m_ParticleSize.x, data[i].m_ParticleSize.y,
				GetColor(data[i].m_RColor,
					data[i].m_GColor,
					data[i].m_BColor), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

void Particle::TitleDraw()
{
	for (int i = 0; i < kMaxParticle; i++)
	{
		if (data[i].m_Exist)
		{
			DrawOval(data[i].m_Pos.x, data[i].m_Pos.y,
				data[i].m_ParticleSize.x, data[i].m_ParticleSize.y,
				GetColor(data[i].m_RColor,
					data[i].m_GColor,
					data[i].m_BColor), true);
		}
	}
}
