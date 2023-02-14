#include "Player.h"
#include "SceneTitle.h"
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

	// フレームタイム
	constexpr int kFrameTime = 20;

	// 重力の強さ
	constexpr float kBigGravity = 1.2f;
	constexpr float kGravity = 0.8f;
	constexpr float kSmallGravity = 0.5f;

	// 動き始めのプレイヤーのスピード
	constexpr float kStartMoveSpeed = 6.0f;

	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeed = 12.0f;
	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeedDown = 0.5f;

	// ヒールゲージ最大
	constexpr int kMaxHealGauge = 90;
}

//Player::Player(handle) :m_handle = handle 

Player::Player() :
m_pos(kFristPlayerPosX + (kSideSize / 2), kFristPlayerPosY),
m_vec(3, 0),
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
m_HitAttack(false),
m_AttackPower(10),
m_Hp(3),
m_MaxHp(3),
m_NoDamageFrame(0),
m_KnockBack(kKnockBackSpeed),
m_PossibleTwoJump(false),
m_HealFrame(0),
m_Vel(0,0),
m_HealGauge(kMaxHealGauge),
m_Exist(true),
m_SceneTitle(nullptr)
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
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
	if (m_Exist)
	{
		IsMoveStart();

		if (m_Hp <= 0)
		{
			m_Exist = false;
		}

		if (m_NoDamageFrame == 100)
		{
			m_Jump = 0;
			m_KnockBack = kKnockBackSpeed;
		}

		if (m_NoDamageFrame >= 0)
		{
			m_NoDamageFrame--;
		}

		if (m_NoDamageFrame > 0)
		{
			IsKnockBack(m_EnemyPos);
		}

		CharaMove();

		LimitMove();
	}
	else if (!m_Exist)
	{
		if (!m_CollBottom)
		{
			m_pos.y += m_Gravity;
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
}

void Player::draw()
{
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

	if (m_PossibleTwoJump)
	{
		DrawString(0,500, "二段ジャンプ可能", GetColor(0, 255, 0));
	}

	DrawFormatString(0, 300, GetColor(255, 255, 255), "プレイヤー体力%d", m_Hp);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "攻撃力%d", m_AttackPower);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "回復ゲージ%d", m_HealGauge);
#ifdef _DEBUG
#endif

	if (m_NoDamageFrame > 0)
	{
		if ((m_NoDamageFrame / 10) % 2 == 0)
		{
			return;
		}
	}

	if (!m_LookLeft)
	{
		DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[(m_CharaGraphY * 8) + m_CharaGraphX], true);
	}

	else if (m_LookLeft)
	{
		DrawTurnGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[(m_CharaGraphY * 8) + m_CharaGraphX], true);
	}

}

void Player::CharaMove()
{
	Pad::update();

	m_FrameChangeSpeed = 1;

	if (Pad::isPress(PAD_INPUT_RIGHT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = false;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		//	m_pos.x += m_vec.x * 2;

		//	if (m_CollRight) m_pos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = true;
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		//	m_pos.x -= m_vec.x * 2;

		//	if(m_CollLeft) m_pos.x += m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		if(!m_Attack) m_LookLeft = false;
		
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		//	m_pos.x += m_vec.x;

		//	if (m_CollRight) m_pos.x -= m_vec.x;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		if (!m_Attack) m_LookLeft = true;
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		//	m_pos.x -= m_vec.x;

		//
		if (m_CollLeft) m_pos.x += m_vec.x;
	}

	else
	{
		IsMoveStop();
		m_CharaGraphY = 0;
		m_CharaMotion = 2;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_NowJump && !m_UseTwoJump)
	{
		m_TwoJump = true;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && !m_NowJump/* && !m_CollBottom && m_PossibleTwoJump*/)
	{
		m_Jump = 14;
		m_NowJump = true;
	}


	if (m_NowJump)
	{
		CharaJump();
	}

	IsHeal();

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
		m_pos.y += m_Gravity;
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
		m_HitAttack = false;
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
	if (m_TwoJump && m_PossibleTwoJump)
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
	m_pos.y -= m_Jump;

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
			m_Jump = 14;
		//	m_pos.y = Game::kScreenHeight - kColumnSize;
		}
	}

}

void Player::LimitMove()
{
	if (m_pos.x < 0 - 35)
	{
		m_pos.x = -35;
	}
	if (m_pos.x > Game::kScreenWidth - kSideSize + 35)
	{
		m_pos.x = Game::kScreenWidth - kSideSize + 35;
	}
	/*if (m_pos.y > Game::kScreenHeight - kColumnSize)
	{
		m_pos.y = Game::kScreenHeight - kColumnSize;
	}*/
}

void Player::NotExist()
{
	m_Jump = 0;
	m_Hp = m_MaxHp;
	m_HealGauge = 0;
}

void Player::IsMoveStart()
{
	if (m_LookLeft)
	{
		if (m_pos.x < kFristPlayerPosX + (kSideSize / 2) + 30)
		{
			m_StartMove = kStartMoveSpeed;
			m_pos.x += m_StartMove;
		}

		else
		{
			m_StartMove = 0;
		}
	}

	if (!m_LookLeft)
	{
		if (m_pos.x > kFristPlayerPosX + (kSideSize / 2) - 30)
		{
			m_StartMove = -kStartMoveSpeed;
			m_pos.x += m_StartMove;
		}

		else
		{
			m_StartMove = 0;
		}
	}
}

void Player::IsMoveStop()
{
	/*m_StartMove = 0;

	if (m_pos.x > kFristPlayerPosX + (kSideSize / 2) + 10 && m_LookLeft)
	{
		m_StartMove = -kStartMoveSpeed;
		m_pos.x += m_StartMove;
	}

	if (m_pos.x < kFristPlayerPosX + (kSideSize / 2) - 10 && !m_LookLeft)
	{
		m_StartMove = kStartMoveSpeed;
		m_pos.x += m_StartMove;
	}*/
}

void Player::Ondamage()
{
	m_Hp--;
}

void Player::IsKnockBack(Vec2 EnemyPos)
{
	if (m_NoDamageFrame <= 0)
	{
		m_Vel.x = 0;
		m_Vel.y = 0;
		return;
	}

	if (m_KnockBack <= 0)
	{
		m_Vel.x = 0;
		m_Vel.y = 0;
		return;
	}
	m_Vel = m_pos - EnemyPos;

	m_Vel = m_Vel.normalize();
	m_Vel *= m_KnockBack;
	m_KnockBack -= kKnockBackSpeedDown;
	if (m_KnockBack > 0)
	{
		m_pos.y += m_Vel.y;
	}
}

void Player::IsHeal()
{
	if (Pad::isPress(PAD_INPUT_2) && m_HealGauge >= 30 && m_Hp < m_MaxHp)
	{
		m_HealFrame++;

		/*if (m_HealFrame > 30)
		{
			m_HealGauge--;
		}*/
		if (m_HealFrame >= 60)
		{
			m_Hp++;
			m_HealFrame = 0;
			m_HealGauge -= 30;
		}
	}

	else
	{
		m_HealFrame = 0;
	}


	if (m_HealGauge <= 0)
	{
		m_HealGauge = 0;
	}
}

void Player::IsHealGauge()
{
	if(m_HealGauge < kMaxHealGauge) m_HealGauge += 10;
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
