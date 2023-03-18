#include "Player.h"
#include "SceneTitle.h"
#include "PlayerShot.h"
#include "Particle.h"
#include "Map.h"
#include <DxLib.h>
#include <cassert>
#include"game.h"
#include"Pad.h"

namespace
{
	//// プレイヤーの初期位置
	//constexpr float kFristPlayerPosX = 760.0f;
	//constexpr float kFristPlayerPosY = 500.0f;

	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";
	const char* const kPlayerHpFilename = "data/Hp1.png";
	const char* const kPlayerGaugeFilename = "data/gauge.png";
	const char* const kPlayerGauge1Filename = "data/gauge1.png";

	// サウンドファイル名
	const char* const kPlayerSoundAttackFilename = "sound/Attack.mp3";
	const char* const kPlayerSoundJumpFilename = "sound/jump.mp3";
	const char* const kPlayerSoundWalkFilename = "sound/walk.mp3";
	const char* const kPlayerSoundDashFilename = "sound/dash.mp3";
	const char* const kPlayerSoundDamageFilename = "sound/Damage.mp3";

	// フレームタイム
	constexpr int kFrameTime = 20;

	// 重力の強さ
	constexpr float kBigGravity = 1.2f;
	constexpr float kGravity = 0.8f;
	constexpr float kSmallGravity = 0.5f;

	// ジャンプ力
	constexpr float kJump = 14.0f;

	// 動き始めのプレイヤーのスピード
	constexpr float kStartMoveSpeed = 6.0f;

	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeedDown = 0.5f;

	// ヒールゲージ最大
	constexpr int kMaxHealGauge = 90;

	// Hp画像の大きさ
	constexpr int kHpSize = 64;

	// ショット間隔
	constexpr int kShotInterval = 20;
}

//Player::Player(handle) :m_handle = handle 

Player::Player() :
m_pos(200, 1000),
m_NextPos(m_pos),
m_vec(5, 0),
m_ShotPos(0,0),
m_StartMove(0),
m_Jump(0.0f),
m_CharaGraphX(0),
m_CharaGraphY(0),
m_FrameChangeChara(0),
m_FrameChangeSpeed(0),
m_CharaMotion(0),
m_Gravity(0),
m_NowDash(false),
m_LookLeft(false),
m_NowJump(false),
m_TwoJump(false),
m_UseTwoJump(false),
m_Coll_Ground(false),
m_CollTop(false),
m_CollBottom(false),
m_CollLeft(false),
m_CollRight(false),
m_Attack(false),
m_InitAttack(true),
m_AttackPower(10),
m_Hp(1000),
m_MaxHp(3),
m_NoDamageFrame(0),
m_KnockBack(0),
m_PossibleTwoJump(true),
m_PushFrame(0),
m_Gauge(kMaxHealGauge),
m_MaxGauge(kMaxHealGauge),
m_PossibleShot(false),
m_ShotIntervalFrame(0),
m_StageClear(false),
m_Exist(true),
m_Map(std::make_shared<Map>()),
m_Shot(nullptr),
m_SceneTitle(nullptr),
m_Particle(std::make_shared<Particle>())
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	
	m_Hphandle = LoadGraph(kPlayerHpFilename);
	m_Gaugehandle = LoadGraph(kPlayerGaugeFilename);
	m_Gauge1handle = LoadGraph(kPlayerGauge1Filename);

	m_SoundAttack = LoadSoundMem(kPlayerSoundAttackFilename);
	m_SoundJump = LoadSoundMem(kPlayerSoundJumpFilename);
	m_SoundWalk = LoadSoundMem(kPlayerSoundWalkFilename);
	m_SoundDash = LoadSoundMem(kPlayerSoundDashFilename);
	m_SoundDamage = LoadSoundMem(kPlayerSoundDamageFilename);
}

Player::~Player()
{

}

void Player::Init()
{
	/*LoadDivGraph(kPlayerGraphicFilename, kCharaChipNum,
		kSideCharaChipNum, kColumnCharaChipNum,
		kSideSize, kColumnSize, m_handle);	*/
}

void Player::end()
{
}

void Player::update()
{
//	m_StageClear = false;
	if (m_Exist)
	{
		if (m_Hp <= 0)
		{
			m_Exist = false;
		}

		if (m_NoDamageFrame == 100)
		{
			m_Jump = 0.0f;
			//	m_KnockBack = kKnockBackSpeed;
		}

		if (m_NoDamageFrame >= 0)
		{
			m_NoDamageFrame--;
		}

		CollGimmick();

		if (m_KnockBack > 0)
		{
			IsKnockBack(m_EnemyPos);
		}

		if (IsShotColl())
		{
			m_Shot->SetExist(false);
		}

		if (m_Shot != nullptr)
		{
			m_Shot->Update();
			m_ShotPos = m_Shot->GetPos();

			if (!m_Shot->GetExist())
			{
				delete m_Shot;
				m_Shot = nullptr;
				m_ShotPos = { 50000,50000 }; // とりあえず絶対に当たらない位置に
			}
		}

		CharaMove();

		IsSound();

		InitColl();

		LimitMove();
	}

	m_Particle->Update();
	IsColl();

	if (!m_Exist)
	{
		/*IsColl();*/
		if (!m_CollBottom)
		{
			m_NextPos.y += m_Gravity;
			m_Gravity += kGravity;
		}

		else
		{
			m_Gravity = 0;
		}

		m_CharaGraphY = 7;
		m_CharaMotion = 8;
		m_FrameChangeSpeed = 3;

		m_CharaGraphX = 0;
		m_FrameChangeChara += m_FrameChangeSpeed;

		m_CharaGraphX = m_FrameChangeChara / kFrameTime;

		if (m_CharaGraphX >= 7)
		{
			m_CharaGraphX = 7;
		}
	}

	/*if (!m_CollRight && !m_CollLeft)
	{
		m_pos.x = m_NextPos.x;
	}*/

	if (!m_StageClear)
	{
		if (!m_CollRight && m_pos.x < m_NextPos.x)
		{
			m_pos.x = m_NextPos.x;
		}

		if (!m_CollLeft && m_pos.x > m_NextPos.x)
		{
			m_pos.x = m_NextPos.x;
		}

		if (m_pos.x < Map::kBgNumX[m_Map->GetStageNum()] * Map::kChipSize)
		{
			m_pos.y = m_NextPos.y;
		}
	}

	m_Map->SetPlayerPos(m_pos);
}

void Player::draw(Vec2 offset)
{
	Vec2 pos = m_pos + offset;
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

	/*if (m_PossibleTwoJump)
	{
		DrawString(0,600, "二段ジャンプ可能", GetColor(0, 255, 0));
	}

	if (m_PossibleShot)
	{
		DrawString(0, 700, "ショット可能", GetColor(0, 255, 0));
	}*/

	if (m_Shot != nullptr)
	{
		m_Shot->Draw(offset);

		if (m_Shot->GetPos().x < -offset.x || m_Shot->GetPos().x > -offset.x + Game::kScreenWidth)
		{
			m_Shot->SetExist(false);
		}
	}


	/*DrawFormatString(0, 300, GetColor(255, 255, 255), "プレイヤー体力%d", m_Hp);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "攻撃力%d", m_AttackPower);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "回復ゲージ%d", m_Gauge);*/
#ifdef _DEBUG
	/*DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);*/
#endif

	for (int i = 0; i < m_MaxHp; i++)
	{
		DrawRectGraph(i * kHpSize + 240, 0, kHpSize, 0, kHpSize, kHpSize,m_Hphandle, true);
		if (m_Hp > i)
		{
			DrawRectGraph(i * kHpSize + 240, 0, 0, 0, kHpSize, kHpSize, m_Hphandle, true);
		}
	}

	DrawRectGraph(120, -(90 * 1.3) + 117, 0,
		-(90 * 1.3) + 117, 117, m_Gaugehandle,
		m_Gaugehandle, true);

	if (m_Gauge >= 30)
	{
		DrawRectGraph(120, -(m_Gauge * 1.3) + 117 - m_MinusGauge, 0,
			-(m_Gauge * 1.3) + 117 - m_MinusGauge, 117, m_Gaugehandle,
			m_Gauge1handle, true);
	}

	else if (m_Gauge < 30)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRectGraph(120, -(m_Gauge * 1.3) + 117 - m_MinusGauge, 0,
			-(m_Gauge * 1.3) + 117 - m_MinusGauge, 117, m_Gaugehandle,
			m_Gauge1handle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	/*DrawGraph(120, 0, m_Gauge1handle, true);
	DrawRectGraph(120,0,0, 0, 117, 117 - (m_Gauge * 1.3) - m_MinusGauge, m_Gaugehandle, true);*/

	if (m_MaxGauge > 90)
	{
		DrawRectGraph(0,-((m_MaxGauge - 90) * 1.3) + 117, 0,
			-((m_MaxGauge - 90) * 1.3) + 117, 117, m_Gaugehandle,
			m_Gaugehandle, true);

		DrawRectGraph(0, -((m_Gauge - 90) * 1.3) + 117 - m_MinusGauge, 0,
			-((m_Gauge - 90) * 1.3) + 117 - m_MinusGauge,117, m_Gaugehandle,
			m_Gauge1handle, true);
	}

	if (m_MinusGauge > 0)
	{
		m_MinusGauge--;
	}

	if (m_NoDamageFrame > 0)
	{
		if ((m_NoDamageFrame / 10) % 2 == 0)
		{
			return;
		}
	}

	if (!m_LookLeft)
	{
		DrawGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), m_handle[(m_CharaGraphY * 8) + m_CharaGraphX], true);
	}

	else if (m_LookLeft)
	{
		DrawTurnGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), m_handle[(m_CharaGraphY * 8) + m_CharaGraphX], true);
	}

	m_Particle->Draw(offset);
}

void Player::CharaMove()
{
	m_InitAttack = true;
	m_NextPos = m_pos;

	m_FrameChangeSpeed = 1;
	
	if (Pad::isPress(PAD_INPUT_RIGHT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = false;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		if(m_KnockBack <= 0 && m_PushFrame <= 30 && !m_CollRight) m_NextPos.x += m_vec.x * 2;

		//	if (m_CollRight) m_NextPos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = true;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		if (m_KnockBack <= 0 && m_PushFrame <= 30 && !m_CollLeft) m_NextPos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		if(!m_Attack) m_LookLeft = false;
		
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		if (m_KnockBack <= 0 && m_PushFrame <= 30 && !m_CollRight) m_NextPos.x += m_vec.x;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		if (!m_Attack) m_LookLeft = true;
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		if (m_KnockBack <= 0 && m_PushFrame <= 30 && !m_CollLeft) m_NextPos.x -= m_vec.x;
	}

	else
	{
	//	IsMoveStop();
		m_CharaGraphY = 0;
		m_CharaMotion = 2;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && !m_CollBottom && !m_UseTwoJump && m_PossibleTwoJump && m_PushFrame <= 30)
	{
		m_NowJump = true;
		m_TwoJump = true;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && !m_NowJump && m_CollBottom && m_PushFrame <= 30)
	{
		m_Jump = kJump;
		m_NowJump = true;
	}


	if (m_NowJump)
	{
		CharaJump();
	}

	/*IsActiveGauge();*/

	if (m_SceneTitle != nullptr)
	{
		if (m_SceneTitle->isTitleEnd())
		{
			m_CharaMotion = 8;
			m_FrameChangeSpeed = 1;
			m_CharaGraphY = 6;
		}
	}

	if (!m_CollBottom && !m_NowJump)
	{
		m_NextPos.y += m_Gravity;
		m_Gravity += kGravity;
	}

	else
	{
		m_Gravity = 0;
	}

	if (m_NowDash)
	{
		m_FrameChangeSpeed = 3;
	}

	if (Pad::isTrigger(PAD_INPUT_5) && !m_Attack || Pad::isTrigger(PAD_INPUT_6) && !m_Attack)
	{
		m_CharaGraphX = 0;
		m_Attack = true;
		m_InitAttack = false;
	}
	else
	{
		/*m_InitAttack = true;*/
	}

	if (m_Attack)
	{
		m_FrameChangeSpeed = 9;
		m_CharaMotion = 8;
		m_CharaGraphY = 8;
		if (m_CharaGraphX == 7)
		{
			m_Attack = false;
			/*m_CharaGraphY = 0;
			m_CharaMotion = 2;*/
		}
	}
	

	IsActiveGauge();

	m_FrameChangeChara += m_FrameChangeSpeed;

	if (m_FrameChangeChara >= kFrameTime)
	{
		m_FrameChangeChara = 0;
		m_CharaGraphX++;
	}

	if (m_CharaGraphX >= m_CharaMotion)
	{
		m_CharaGraphX = 0;
	}
	m_NowDash = false;
}

void Player::CharaJump()
{
	if (m_TwoJump)
	{
		m_TwoJump = false;
		m_UseTwoJump = true;
		m_Jump = kJump;
	}
	if (m_CollTop)
	{
		if(m_Jump > 0.0f) m_Jump = 0.0f;
	}
	m_FrameChangeSpeed = 3;
	m_CharaGraphY = 5;
	m_CharaMotion = 8;
	m_NextPos.y -= m_Jump;

	if (m_Jump >= -25.0f)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			m_Jump -= kSmallGravity;
		}
		else
		{
			m_Jump -= kBigGravity;
		}
	}

	if (/*m_pos.y >= Game::kScreenHeight - kColumnSize ||*/ m_CollBottom)
	{
		if (m_Jump <= 0.0f)
		{
			m_TwoJump = false;
			m_NowJump = false;
			m_UseTwoJump = false;
		//	m_Jump = 14;
		//	m_pos.y = Game::kScreenHeight - kColumnSize;
		}
	}

}

void Player::LimitMove()
{
	if (m_NextPos.x < 0)
	{
		m_NextPos.x = 0;
	}

	/*if (m_NextPos.x > Map::kChipSize * Map::kBgNumX[m_Map->GetStageNum()] - kSideSize)
	{
		m_NextPos.x = Map::kChipSize * Map::kBgNumX[m_Map->GetStageNum()] - kSideSize;
	}*/

	if (FallPlayer())
	{
		m_Exist = false;
	}
}

void Player::NotExist()
{
	m_Jump = 0;
	m_Hp = m_MaxHp;
	m_Gauge = 0;
	m_CharaGraphX = 0;
	m_CharaGraphY = 0;
	m_KnockBack = 0;
}

//void Player::IsMoveStart()
//{
//	if (m_LookLeft)
//	{
//		if (m_pos.x < kFristPlayerPosX + (kSideSize / 2) + 30)
//		{
//			m_StartMove = kStartMoveSpeed;
//			m_pos.x += m_StartMove;
//		}
//
//		else
//		{
//			m_StartMove = 0;
//		}
//	}
//
//	if (!m_LookLeft)
//	{
//		if (m_pos.x > kFristPlayerPosX + (kSideSize / 2) - 30)
//		{
//			m_StartMove = -kStartMoveSpeed;
//			m_pos.x += m_StartMove;
//		}
//
//		else
//		{
//			m_StartMove = 0;
//		}
//	}
//}

//void Player::IsMoveStop()
//{
//	/*m_StartMove = 0;
//
//	if (m_pos.x > kFristPlayerPosX + (kSideSize / 2) + 10 && m_LookLeft)
//	{
//		m_StartMove = -kStartMoveSpeed;
//		m_pos.x += m_StartMove;
//	}
//
//	if (m_pos.x < kFristPlayerPosX + (kSideSize / 2) - 10 && !m_LookLeft)
//	{
//		m_StartMove = kStartMoveSpeed;
//		m_pos.x += m_StartMove;
//	}*/
//}

void Player::Ondamage()
{
	m_Hp--;
	m_NoDamageFrame = 100;
	m_Particle->SetPos(m_pos);
	m_Particle->SetdamagePlayerParticle();
	m_Damage = true;
}

void Player::IsKnockBack(Vec2 EnemyPos)
{
	Vec2 Vel = m_NextPos - EnemyPos;

	Vel = Vel.normalize();
	Vel *= m_KnockBack;
	m_KnockBack -= kKnockBackSpeedDown;

	/*if (m_NoDamageFrame <= 0)
	{
		Vel.x = 0;
		Vel.y = 0;
		return;
	}*/

	if (m_KnockBack <= 0)
	{
		Vel.x = 0;
		Vel.y = 0;
		return;
	}

	m_NextPos.x += Vel.x;

	if (!m_CollRight && Vel.x > 0)
	{
		m_pos.x = m_NextPos.x;
	}

	if (!m_CollLeft && Vel.x < 0)
	{
		m_pos.x = m_NextPos.x;
	}
}

void Player::IsActiveGauge()
{
	if (m_ShotIntervalFrame > 0)
	{
		m_ShotIntervalFrame--;
	}

	if (Pad::isPress(PAD_INPUT_2) && m_Gauge >= 30)
	{
		if (m_PushFrame >= 30 && m_Hp == m_MaxHp)
		{
			m_PushFrame--;
		}
		m_PushFrame++;

		if (m_PushFrame > 30 && m_Hp < m_MaxHp)
		{
			Vec2 CenterPos = { m_pos.x + (kSideSize / 2) ,m_pos.y + kColumnSize - 20 };

			m_Particle->SetPos(CenterPos);
			m_Particle->SetPlayerParticle();

			m_CharaGraphY = 0;
			m_CharaMotion = 2;
		}

		/*if (m_HealFrame > 30)
		{
			m_HealGauge--;
		}*/
		if (m_PushFrame == 90 && m_Hp < m_MaxHp)
		{
			if (m_Hp < m_MaxHp)
			{
				m_Hp++;
			}
			m_PushFrame = 30;
			m_Gauge -= 30;
			m_MinusGauge += 30;
		}
	}
	else if(m_PushFrame > 0 && m_PushFrame < 30 && !m_Attack
		&& m_Gauge >= 30 && m_ShotIntervalFrame <= 0 && m_PossibleShot)
	{
		if (m_Shot == nullptr)
		{
			if (m_LookLeft)
			{
				m_Shot = new PlayerShot({ m_pos.x,m_pos.y + (kColumnSize / 4) }, -40.0f);
				m_Particle->SetPos({ m_pos.x,m_pos.y + (kColumnSize / 2 + 10) });
			}
			else if (!m_LookLeft)
			{
				m_Shot = new PlayerShot({ m_pos.x + (kSideSize / 2),m_pos.y + (kColumnSize / 4) }, 40.0f);
				m_Particle->SetPos({ m_pos.x + kSideSize, m_pos.y + (kColumnSize / 2 + 10) });
			}
			m_InitAttack = false;
			m_Gauge -= 30;
			m_MinusGauge += 30;
		}
		else if(m_Shot != nullptr)
		{
			m_PushFrame = 0;
			return;
		}
		m_ShotPos = m_Shot->GetPos();
		m_PushFrame = 0;
		m_ShotIntervalFrame = kShotInterval;
		/*m_Particle->SetPos(m_pos);*/
		m_Particle->SetShotPlayerParticle();
	//	m_Gauge -= 30;
	}
	else
	{
		m_PushFrame = 0;
	}

	if (m_Gauge <= 0)
	{
		m_Gauge = 0;
	}
}

void Player::IsGauge()
{
	if(m_Gauge < m_MaxGauge) m_Gauge += 10;
}

//void Player::IsColl()
//{
//	float PlayerTop = m_NextPos.y;
//	float PlayerBottom = m_NextPos.y + Player::kSideSize;
//	float PlayerLeft = m_NextPos.x;
//	float PlayerRight = m_NextPos.x + Player::kSideSize;
//
//	for (int i = 0; i < Map::kBgNumY; i++)
//	{
//		for (int j = 0; j < Map::kBgNumX; j++)
//		{
//			float MapPosX = j * Map::kChipSize;
//			float MapPosY = i * Map::kChipSize;
//			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 2)
//			{
//				/*float MapPosX = j * Map::kChipSize;
//				float MapPosY = i * Map::kChipSize;*/
//
//				if (m_NextPos.y + 10 < MapPosY + Map::kChipSize - 40 &&
//					m_NextPos.y > MapPosY &&
//					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_CollTop = true;
//				}
//				//上
//				if (m_NextPos.y + 10 < MapPosY + Map::kChipSize &&
//					m_NextPos.y > MapPosY &&
//					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_CollTop = true;
//				}
//				//右
//				if (m_NextPos.x + Player::kSideSize - 35 > MapPosX &&
//					m_NextPos.x + 60 < MapPosX + Map::kChipSize &&
//					m_NextPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_NextPos.y + (Map::kChipSize * 2) > MapPosY + 20)
//				{
//					m_CollRight = true;
//				}
//				//左
//				if (m_NextPos.x + 35 < MapPosX + Map::kChipSize &&
//					m_NextPos.x + Player::kSideSize - 60 > MapPosX &&
//					m_NextPos.y + 25 < MapPosY + Map::kChipSize &&
//					m_NextPos.y + (Map::kChipSize * 2) > MapPosY + 20)
//				{
//					m_CollLeft = true;
//				}
//				//下
//				if (m_NextPos.y + (Player::kColumnSize) > MapPosY &&
//					m_NextPos.y + 25 < MapPosY/* + Minigame1::kChipSize*/ &&
//					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
//					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
//				{
//					m_NextPos.y = MapPosY - (Player::kColumnSize)+1;
//					m_CollBottom = true;
//				}
//
//				//ステージクリアの判定
//			}
//
//			if (m_Map->GetMapData(i, j) > Map::kSideMapChipNum * 2 
//				&& m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 7)
//			{
//
//				if (PlayerTop > MapPosY + Map::kChipSize) continue;
//				if (PlayerBottom < MapPosY) continue;
//				if (PlayerLeft > MapPosX + +Map::kChipSize) continue;
//				if (PlayerRight < MapPosX) continue;
//
//				if ((Pad::isTrigger(PAD_INPUT_UP)))
//				{
//					m_StageClear = true;
//				}
//			}
//		}
//	}
//
//}

void Player::IsColl()
{
	float PlayerTop = m_NextPos.y;
	float PlayerBottom = m_NextPos.y + Player::kSideSize;
	float PlayerLeft = m_NextPos.x + 40;
	float PlayerRight = m_NextPos.x + Player::kSideSize - 40;

	// プレイヤーの中心座標: X軸
	float PlayerCentor = m_NextPos.x + (Player::kSideSize / 2);

	for (int i = 0; i < Map::kBgNumY[m_Map->GetStageNum()]; i++)
	{
		for (int j = 0; j < Map::kBgNumX[m_Map->GetStageNum()]; j++)
		{
			float MapTop = i * Map::kChipSize;
			float MapBottom = i * Map::kChipSize + Map::kChipSize;
			float MapRight = j * Map::kChipSize + Map::kChipSize;
			float MapLeft = j * Map::kChipSize;

			if (m_Map->GetMapData(i, j) == 10)
			{
				MapRight -= 20;
				MapLeft += 20;
			}

			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 2)
			{
				if (m_Map->GetMapData(i, j) != 11 && m_Map->GetMapData(i, j) != 12 &&
					m_Map->GetMapData(i, j) != 27 && m_Map->GetMapData(i, j) != 28)
				{
					//下
					if (PlayerBottom > MapTop &&
						PlayerTop < MapTop &&
						PlayerRight > MapLeft + 10 &&
						PlayerLeft < MapRight - 10 &&
						m_Jump <= 0.0f)
					{
						m_NextPos.y = MapTop - Player::kColumnSize + 10;
						PlayerBottom = m_NextPos.y + Player::kColumnSize;
						m_CollBottom = true;
					}
					//上
					if (PlayerTop < MapBottom &&
						PlayerRight > MapLeft + 10 &&
						PlayerLeft < MapRight - 10 &&
						PlayerTop >= MapTop)
					{
						m_CollTop = true;
					}
					//右
					if (PlayerRight >= MapLeft &&
						PlayerLeft <= MapRight &&
						PlayerTop < MapBottom - 20 &&
						PlayerBottom > MapTop + 30 &&
						PlayerCentor < MapLeft)
					{
						m_CollRight = true;
					}
					//左
					if (PlayerRight >= MapLeft &&
						PlayerLeft <= MapRight &&
						PlayerTop < MapBottom - 20 &&
						PlayerBottom > MapTop + 30 &&
						PlayerCentor > MapRight)
					{
						m_CollLeft = true;
					}
				}

				if (m_Map->GetMapData(i, j) == 11 || m_Map->GetMapData(i, j) == 12 ||
					m_Map->GetMapData(i, j) == 27 || m_Map->GetMapData(i, j) == 28)
				{
					if (m_Map->GetBossBattle())
					{
						//下
						if (PlayerBottom > MapTop &&
							PlayerTop < MapTop &&
							PlayerRight > MapLeft + 10 &&
							PlayerLeft < MapRight - 10 &&
							m_Jump <= 0.0f)
						{
							m_NextPos.y = MapTop - Player::kColumnSize + 10;
							PlayerBottom = m_NextPos.y + Player::kColumnSize;
							m_CollBottom = true;
						}
						//上
						if (PlayerTop < MapBottom &&
							PlayerRight > MapLeft + 10 &&
							PlayerLeft < MapRight - 10 &&
							PlayerTop >= MapTop)
						{
							m_CollTop = true;
						}
						//右
						if (PlayerRight >= MapLeft &&
							PlayerLeft <= MapRight &&
							PlayerTop < MapBottom - 20 &&
							PlayerBottom > MapTop + 30 &&
							PlayerCentor < MapLeft)
						{
							m_CollRight = true;
						}
						//左
						if (PlayerRight >= MapLeft &&
							PlayerLeft <= MapRight &&
							PlayerTop < MapBottom - 20 &&
							PlayerBottom > MapTop + 30 &&
							PlayerCentor > MapRight)
						{
							m_CollLeft = true;
						}
					}
				}
				//ステージクリアの判定
			}

			/*if (m_Map->GetMapData(i, j) > Map::kSideMapChipNum * 2
				&& m_Map->GetMapData(i, j) <= Map::kSideMapChipNum * 7)*/
			if (m_NextPos.x >= Map::kBgNumX[m_Map->GetStageNum()] * Map::kChipSize - 60)
			{
				m_StageClear = true;

				/*if (PlayerTop > MapBottom) continue;
				if (PlayerBottom < MapTop) continue;
				if (PlayerLeft > MapRight) continue;
				if (PlayerRight < MapLeft) continue;

				if ((Pad::isTrigger(PAD_INPUT_UP)))
				{
				}*/
			}
		}
	}

}

bool Player::IsShotColl()
{
	if (m_Shot == nullptr)
	{
		return false;
	}

	Vec2 ShotPos = m_Shot->GetPos();

	float ShotPosTop = ShotPos.y;
	float ShotPosBottom = ShotPos.y + 50;
	float ShotPosLeft = ShotPos.x;
	float ShotPosRight = ShotPos.x + 50;

	for (int i = 0; i < Map::kBgNumY[m_Map->GetStageNum()]; i++)
	{
		for (int j = 0; j < Map::kBgNumX[m_Map->GetStageNum()]; j++)
		{
			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= 50)
			{
				float MapPosX = j * Map::kChipSize;
				float MapPosY = i * Map::kChipSize;

				if (ShotPosTop > MapPosY + Map::kChipSize) continue;
				if (ShotPosBottom < MapPosY) continue;
				if (ShotPosLeft > MapPosX + +Map::kChipSize) continue;
				if (ShotPosRight < MapPosX) continue;

				return true;
			}
		}
	}
	return false;
}

void Player::InitColl()
{
	m_CollTop = false;
	m_CollBottom = false;
	m_CollRight = false;
	m_CollLeft = false;
}

bool Player::PushButton()
{
	//現在のパッドの状態を取得
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// Bボタンを押したときだけ反応
	if (padState == (PAD_INPUT_2))
	{
		return true;
	}

	return false;
}

bool Player::FallPlayer()
{
	if (m_pos.y > Map::kBgNumY[m_Map->GetStageNum()] * Map::kChipSize)
	{
		return true;
	}

	return false;
}

void Player::MaxHpUp()
{
	m_MaxHp++;
}

void Player::MaxGaugeUp()
{
	m_MaxGauge += 30;
}

void Player::CollGimmick()
{
	float PlayerTop = m_pos.y;
	float PlayerBottom = m_pos.y + Player::kSideSize;
	float PlayerLeft = m_pos.x + 40;
	float PlayerRight = m_pos.x + Player::kSideSize - 40;

	for (int i = 0; i < m_Map->GetGimmickCount(); i++)
	{
		if (!m_Map->GetGimmickFlag(i))
		{
			continue;
		}
		Vec2 GimmickPos = m_Map->GetGimmickPos(i);
		Vec2 GimmickGraphSize1 = m_Map->GetGimmickSize1(i);
		Vec2 GimmickGraphSize2 = m_Map->GetGimmickSize2(i);

		float GimmickPosTop = GimmickPos.y + GimmickGraphSize1.y;
		float GimmickPosBottom = GimmickPos.y + GimmickGraphSize2.y;
		float GimmickPosLeft = GimmickPos.x + GimmickGraphSize1.x;
		float GimmickPosRight = GimmickPos.x + GimmickGraphSize2.x;

#ifdef _DEBUG
	/*DrawBox(GimmickPosLeft, GimmickPosTop,
		GimmickPosRight, GimmickPosBottom,
			0xffffff, false);*/
#endif

		if (PlayerTop > GimmickPosBottom) continue;
		if (PlayerBottom < GimmickPosTop) continue;
		if (PlayerLeft > GimmickPosRight) continue;
		if (PlayerRight < GimmickPosLeft) continue;

		if (m_NoDamageFrame <= 0)
		{
			Ondamage();
			PlaySoundMem(m_SoundDamage, DX_PLAYTYPE_BACK);
			m_KnockBack = kKnockBackSpeed;
			m_EnemyPos = GimmickPos;
			return;
		}
		
	}

}

bool Player::CollNeedle()
{
	float PlayerTop = m_pos.y;
	float PlayerBottom = m_pos.y + Player::kSideSize;
	float PlayerLeft = m_pos.x + 40;
	float PlayerRight = m_pos.x + Player::kSideSize - 40;

	for (int i = 0; i < Map::kBgNumY[m_Map->GetStageNum()]; i++)
	{
		for (int j = 0; j < Map::kBgNumX[m_Map->GetStageNum()]; j++)
		{
			if (m_Map->GetMapData(i, j) == 10)
			{
				float MapTop = i * Map::kChipSize;
				float MapBottom = i * Map::kChipSize + Map::kChipSize;
				float MapRight = j * Map::kChipSize + Map::kChipSize - 10;
				float MapLeft = j * Map::kChipSize + 10;

				if (PlayerLeft > MapRight) continue;
				if (PlayerRight < MapLeft) continue;
				if (PlayerTop > MapBottom) continue;
				if (PlayerBottom < MapTop) continue;

				return true;
			}				
		}
	}
	return false;
}

void Player::IsSound()
{
	if (m_CollBottom)
	{
		if (/*Pad::isPress(PAD_INPUT_RIGHT) || Pad::isPress(PAD_INPUT_LEFT)*/m_pos.x != m_NextPos.x)
		{
			if (Pad::isPress(PAD_INPUT_3) && !CheckSoundMem(m_SoundDash))
			{
				PlaySoundMem(m_SoundDash, DX_PLAYTYPE_BACK);
				StopSoundMem(m_SoundWalk);
			}
			else if(!Pad::isPress(PAD_INPUT_3) && !CheckSoundMem(m_SoundWalk))
			{
				PlaySoundMem(m_SoundWalk, DX_PLAYTYPE_BACK);
				StopSoundMem(m_SoundDash);
			}
		}

		else
		{
			StopSoundMem(m_SoundDash);
			StopSoundMem(m_SoundWalk);
		}
	}

	if(!m_CollBottom)
	{
		StopSoundMem(m_SoundDash);
		StopSoundMem(m_SoundWalk);
	}


	if (m_Attack)
	{
		if (!CheckSoundMem(m_SoundAttack))
		{
			PlaySoundMem(m_SoundAttack, DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		StopSoundMem(m_SoundAttack);
	}

	if (!CheckSoundMem(m_SoundJump) && Pad::isTrigger(PAD_INPUT_1) && !m_UseTwoJump)
	{
		if(m_Jump >= 13.5f)
		PlaySoundMem(m_SoundJump, DX_PLAYTYPE_BACK);
	}

	if (m_UseTwoJump && m_Jump >= 13.5f)
	{
		PlaySoundMem(m_SoundJump, DX_PLAYTYPE_BACK);
	}
}














//if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	//{
	//	IsMoveStartRight();
	//	m_NowDash = true;
	//	m_LookLeft = false;
	//	m_CharaGraphY = 3;
	//	m_CharaMotion = 8;
	////	m_pos.x += m_vec.x * 2;

	////	if (m_CollRight) m_pos.x -= m_vec.x * 2;
	//}

	//else if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	//{
	//	IsMoveStartLeft();
	//	m_NowDash = true;
	//	m_LookLeft = true;
	//	m_CharaGraphY = 3;
	//	m_CharaMotion = 8;
	////	m_pos.x -= m_vec.x * 2;
	//	
	////	if(m_CollLeft) m_pos.x += m_vec.x * 2;
	//}

	//else if (CheckHitKey(KEY_INPUT_RIGHT))
	//{
	////	IsMoveStop();
	//	m_LookLeft = false;
	//	m_CharaGraphY = 2;
	//	m_CharaMotion = 4;
	////	m_pos.x += m_vec.x;

	////	if (m_CollRight) m_pos.x -= m_vec.x;
	//}

	//else if (CheckHitKey(KEY_INPUT_LEFT))
	//{
	////	IsMoveStop();
	//	m_LookLeft = true;
	//	m_CharaGraphY = 2;
	//	m_CharaMotion = 4;
	////	m_pos.x -= m_vec.x;

	////
	//	if (m_CollLeft) m_pos.x += m_vec.x;
	//}

	//else
	//{
	//	IsMoveStop();
	//	m_CharaGraphY = 0;
	//	m_CharaMotion = 2;
	//}

	//if (Pad::isTrigger(PAD_INPUT_10) && !m_CollBottom && m_PossibleTwoJump)
	//{
	//	m_NowJump = true;
	//	m_TwoJump = true;
	//}

	//if (Pad::isTrigger(PAD_INPUT_10) && m_CollBottom)
	//{
	//	m_NowJump = true;
	//	m_CollBottom = false;
	//}

	//if (m_NowJump)
	//{
 //  		CharaJump();
	//}

 // 	if (m_SceneTitle != nullptr)
	//{
	//	if (m_SceneTitle->isTitleEnd())
	//	{
	//		m_CharaMotion = 8;
	//		m_FrameChangeSpeed = 1;
	//		m_CharaGraphY = 6;
	//	}
	//}

	//if (!m_CollBottom && !m_NowJump)
	//{
	//	m_pos.y += m_Gravity;
	//	m_Gravity += kGravity;
	//}

	//else
	//{
	//	m_Gravity = 0;
	//}

	//if (m_NowDash)
	//{
	//	m_FrameChangeSpeed = 3;
	//}

	//if (Pad::isTrigger(PAD_INPUT_1) && !m_Attack)
	//{
	//	m_CharaGraphX = 0;
	//	m_Attack = true;
	//	m_HitAttack = false;
	//}

	//if (m_Attack)
	//{
	//	m_FrameChangeSpeed = 9;
	//	m_CharaMotion = 8;
	//	m_CharaGraphY = 8;
	//	if (m_CharaGraphX == 7)
	//	{
	//		m_Attack = false;
	//		/*m_CharaGraphY = 0;
	//		m_CharaMotion = 2;*/
	//	}
	//}

	//m_FrameChangeChara += m_FrameChangeSpeed;

	//if (m_FrameChangeChara >= kFrameTime)
	//{
	//	m_FrameChangeChara = 0;
	//	m_CharaGraphX++;
	//}

	//if (m_CharaGraphX >= m_CharaMotion)
	//{
	//	m_CharaGraphX = 0;
	//}
	//m_NowDash = false;
