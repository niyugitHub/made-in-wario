#include "Player.h"
#include "SceneTitle.h"
#include "PlayerShot.h"
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

	// フレームタイム
	constexpr int kFrameTime = 20;

	// 重力の強さ
	constexpr float kBigGravity = 1.2f;
	constexpr float kGravity = 0.8f;
	constexpr float kSmallGravity = 0.5f;

	// 動き始めのプレイヤーのスピード
	constexpr float kStartMoveSpeed = 6.0f;

	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeedDown = 0.5f;

	// ヒールゲージ最大
	constexpr int kMaxHealGauge = 90;

	// Hp画像の大きさ
	constexpr int kHpSize = 64;

	// ショット間隔
	constexpr int kShotInterval = 30;
}

//Player::Player(handle) :m_handle = handle 

Player::Player() :
m_pos(kFristPlayerPosX + (kSideSize / 2), kFristPlayerPosY),
m_NextPos(m_pos),
m_vec(5, 0),
m_ShotPos(0,0),
m_StartMove(0),
m_Jump(14.0f),
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
m_Hp(3),
m_MaxHp(3),
m_NoDamageFrame(0),
m_KnockBack(0),
m_PossibleTwoJump(false),
m_PushFrame(0),
m_Gauge(kMaxHealGauge),
m_PossibleShot(false),
m_ShotIntervalFrame(0),
m_StageClear(false),
m_Exist(true),
m_Map(std::make_shared<Map>()),
m_Shot(nullptr),
m_SceneTitle(nullptr)
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	
	m_Hphandle = LoadGraph(kPlayerHpFilename);
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
	m_StageClear = false;
	if (m_Exist)
	{
		if (m_Hp <= 0)
		{
			m_Exist = false;
		}

		if (m_NoDamageFrame == 100)
		{
			m_Jump = 0;
		//	m_KnockBack = kKnockBackSpeed;
		}

		if (m_NoDamageFrame >= 0)
		{
			m_NoDamageFrame--;
		}

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


		IsColl();

		CharaMove();

		LimitMove();
	}
	if (!m_Exist)
	{
		IsColl();
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

	IsColl();

	if (!m_CollRight && !m_CollLeft)
	{
		m_pos.x = m_NextPos.x;
	}
	m_pos.y = m_NextPos.y;

	InitColl();
}

void Player::draw(Vec2 offset)
{
	Vec2 pos = m_pos + offset;
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

	if (m_PossibleTwoJump)
	{
		DrawString(0,500, "二段ジャンプ可能", GetColor(0, 255, 0));
	}

	if (m_Shot != nullptr)
	{
		m_Shot->Draw(offset);

		if (m_Shot->GetPos().x < -offset.x || m_Shot->GetPos().x > -offset.x + Game::kScreenWidth)
		{
			m_Shot->SetExist(false);
		}
	}


	DrawFormatString(0, 300, GetColor(255, 255, 255), "プレイヤー体力%d", m_Hp);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "攻撃力%d", m_AttackPower);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "回復ゲージ%d", m_Gauge);
#ifdef _DEBUG
	/*DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);*/
#endif

	for (int i = 0; i < m_MaxHp; i++)
	{
		DrawRectGraph(i * kHpSize, 0, kHpSize, 0, kHpSize, kHpSize,m_Hphandle, true);
		if (m_Hp > i)
		{
			DrawRectGraph(i * kHpSize, 0, 0, 0, kHpSize, kHpSize, m_Hphandle, true);
		}
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
}

void Player::CharaMove()
{
	m_NextPos = m_pos;

	m_FrameChangeSpeed = 1;

	if (Pad::isPress(PAD_INPUT_RIGHT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = false;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		if(m_KnockBack <= 0 && m_PushFrame <= 30) m_NextPos.x += m_vec.x * 2;

		//	if (m_CollRight) m_NextPos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = true;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		if (m_KnockBack <= 0 && m_PushFrame <= 30) m_NextPos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		if(!m_Attack) m_LookLeft = false;
		
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		if (m_KnockBack <= 0 && m_PushFrame <= 30) m_NextPos.x += m_vec.x;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		if (!m_Attack) m_LookLeft = true;
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		if (m_KnockBack <= 0 && m_PushFrame <= 30) m_NextPos.x -= m_vec.x;
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
		m_Jump = 14;
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
		m_InitAttack = true;
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
		m_Jump = 12;
	}
	if (m_CollTop)
	{
		if(m_Jump > 0) m_Jump = 0;
	}
	m_FrameChangeSpeed = 3;
	m_CharaGraphY = 5;
	m_CharaMotion = 8;
	m_NextPos.y -= m_Jump;

	if (Pad::isPress(PAD_INPUT_1))
	{
		m_Jump -= kSmallGravity;
	}
	else
	{
		m_Jump -= kBigGravity;
	}

	if (/*m_pos.y >= Game::kScreenHeight - kColumnSize ||*/ m_CollBottom)
	{
		if (m_Jump <= 0)
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

	if (m_NextPos.x > Map::kChipSize * Map::kBgNumX - kSideSize)
	{
		m_NextPos.x = Map::kChipSize * Map::kBgNumX - kSideSize;
	}

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

	if (m_CollBottom)
	{
		//	m_NextPos += Vel;
		m_pos.x += Vel.x;
	}
	else
	{
		//	m_NextPos += Vel;
		m_pos += Vel;
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
		m_PushFrame++;

		/*if (m_HealFrame > 30)
		{
			m_HealGauge--;
		}*/
		if (m_PushFrame == 90)
		{
			if (m_Hp < m_MaxHp)
			{
				m_Hp++;
			}
			m_PushFrame = 30;
			m_Gauge -= 30;
		}
	}
	else if(m_PushFrame > 0 && m_PushFrame <= 30
		&& m_Gauge >= 30 && m_ShotIntervalFrame <= 0)
	{
		if (m_Shot == nullptr)
		{
			if (m_LookLeft)
			{
				m_Shot = new PlayerShot({ m_pos.x,m_pos.y + (kColumnSize / 4) }, -40.0f);
			}
			else if (!m_LookLeft)
			{
				m_Shot = new PlayerShot({ m_pos.x + (kSideSize / 2),m_pos.y + (kColumnSize / 4) }, 40.0f);
			}
		}
		m_InitAttack = false;
		m_ShotPos = m_Shot->GetPos();
		m_PushFrame = 0;
		m_ShotIntervalFrame = kShotInterval;
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
	if(m_Gauge < kMaxHealGauge) m_Gauge += 10;
}

void Player::IsColl()
{
	float PlayerTop = m_NextPos.y;
	float PlayerBottom = m_NextPos.y + Player::kSideSize;
	float PlayerLeft = m_NextPos.x;
	float PlayerRight = m_NextPos.x + Player::kSideSize;

	for (int i = 0; i < Map::kBgNumY; i++)
	{
		for (int j = 0; j < Map::kBgNumX; j++)
		{
			float MapPosX = j * Map::kChipSize;
			float MapPosY = i * Map::kChipSize;
			if (m_Map->GetMapData(i, j) > 0 && m_Map->GetMapData(i, j) <= 50)
			{
				/*float MapPosX = j * Map::kChipSize;
				float MapPosY = i * Map::kChipSize;*/

				if (m_NextPos.y + 10 < MapPosY + Map::kChipSize - 40 &&
					m_NextPos.y > MapPosY &&
					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
				{
					m_CollTop = true;
				}
				//上
				if (m_NextPos.y + 10 < MapPosY + Map::kChipSize &&
					m_NextPos.y > MapPosY &&
					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
				{
					m_CollTop = true;
				}
				//右
				if (m_NextPos.x + Player::kSideSize - 35 > MapPosX &&
					m_NextPos.x + 60 < MapPosX + Map::kChipSize &&
					m_NextPos.y + 25 < MapPosY + Map::kChipSize &&
					m_NextPos.y + (Map::kChipSize * 2) > MapPosY + 20)
				{
					m_CollRight = true;
				}
				//左
				if (m_NextPos.x + 35 < MapPosX + Map::kChipSize &&
					m_NextPos.x + Player::kSideSize - 60 > MapPosX &&
					m_NextPos.y + 25 < MapPosY + Map::kChipSize &&
					m_NextPos.y + (Map::kChipSize * 2) > MapPosY + 20)
				{
					m_CollLeft = true;
				}
				//下
				if (m_NextPos.y + (Player::kColumnSize) > MapPosY &&
					m_NextPos.y + 25 < MapPosY/* + Minigame1::kChipSize*/ &&
					m_NextPos.x + Player::kSideSize - 50 > MapPosX &&
					m_NextPos.x + 50 < MapPosX + Map::kChipSize)
				{
					m_NextPos.y = MapPosY - (Player::kColumnSize)+1;
					m_CollBottom = true;
				}

				//ステージクリアの判定
			}

			if (m_Map->GetMapData(i, j) > 50 && m_Map->GetMapData(i, j) <= 175)
			{

				if (PlayerTop > MapPosY + Map::kChipSize) continue;
				if (PlayerBottom < MapPosY) continue;
				if (PlayerLeft > MapPosX + +Map::kChipSize) continue;
				if (PlayerRight < MapPosX) continue;

				if ((Pad::isTrigger(PAD_INPUT_UP)))
				{
					m_StageClear = true;
				}
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

	for (int i = 0; i < Map::kBgNumY; i++)
	{
		for (int j = 0; j < Map::kBgNumX; j++)
		{
			if (m_Map->GetMapData(i, j) != 0)
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
	if (m_pos.y > Game::kScreenHeight)
	{
		return true;
	}

	return false;
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
