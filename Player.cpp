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
	constexpr float kStartMoveSpeed = 4.0f;

	// 動き始めのプレイヤーのスピード減少
	constexpr float kStartMoveSpeedDown = 0.2f;

	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeed = 12.0f;
	// ノックバック時のスピード減少量
	constexpr float kKnockBackSpeedDown = 0.5f;
}

//Player::Player(handle) :m_handle = handle 

Player::Player() :
m_pos(kFristPlayerPosX, kFristPlayerPosY),
m_vec(3, 0),
m_StartMove(kStartMoveSpeed),
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
m_IsMove(false),
m_AttackPower(10),
m_Hp(500000),
m_MaxHp(3),
m_NoDamageFrame(0),
m_KnockBack(kKnockBackSpeed),
m_PossibleTwoJump(false),
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

void Player::draw()
{
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

#ifdef _DEBUG
	if (m_PossibleTwoJump)
	{
		DrawString(0,500, "二段ジャンプ可能", GetColor(0, 255, 0));
	}

	DrawFormatString(0, 300, GetColor(255, 255, 255), "プレイヤー体力%d", m_Hp);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "攻撃力%d", m_AttackPower);
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
		IsMoveStartRight();
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		//	m_pos.x += m_vec.x * 2;

		//	if (m_CollRight) m_pos.x -= m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT) && Pad::isPress(PAD_INPUT_3))
	{
		if (!m_Attack) m_LookLeft = true;
		IsMoveStartLeft();
		m_NowDash = true;
		m_CharaGraphY = 3;
		m_CharaMotion = 8;
		//	m_pos.x -= m_vec.x * 2;

		//	if(m_CollLeft) m_pos.x += m_vec.x * 2;
	}

	else if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		//	IsMoveStop();
		if(!m_Attack) m_LookLeft = false;
		
		m_CharaGraphY = 2;
		m_CharaMotion = 4;
		//	m_pos.x += m_vec.x;

		//	if (m_CollRight) m_pos.x -= m_vec.x;
	}

	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		//	IsMoveStop();
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

	if (Pad::isTrigger(PAD_INPUT_1) && !m_CollBottom && m_PossibleTwoJump)
	{
		m_NowJump = true;
		m_TwoJump = true;
	}

	if (Pad::isTrigger(PAD_INPUT_1) && m_CollBottom)
	{
		m_NowJump = true;
		m_CollBottom = false;
	}

	if (m_NowJump)
	{
		CharaJump();
	}

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

	if (Pad::isTrigger(PAD_INPUT_5) || Pad::isTrigger(PAD_INPUT_6) && !m_Attack)
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

}

void Player::CharaJump()
{
	if (m_TwoJump && !m_UseTwoJump && m_PossibleTwoJump)
	{
		m_UseTwoJump = true;
		m_TwoJump = false;
		m_Jump = 14;
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
			m_UseTwoJump = false;
			m_TwoJump = false;
			m_NowJump = false;
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
}

void Player::IsMoveStartLeft()
{
	if (!m_IsMove || m_pos.x < kFristPlayerPosX)
	{
		m_StartMove = kStartMoveSpeed;
		m_IsMove = true;
	}
	
	m_StartMove -= kStartMoveSpeedDown;

	if (m_StartMove > 0)
	{
		m_pos.x += m_StartMove;
	}
	else
	{
		m_StartMove = 0;
	}
}

void Player::IsMoveStartRight()
{
	if (!m_IsMove || m_pos.x > kFristPlayerPosX)
	{
		m_StartMove = -kStartMoveSpeed;
		m_IsMove = true;
	}

	m_StartMove += kStartMoveSpeedDown;

	if (m_StartMove < 0)
	{
		m_pos.x += m_StartMove;
	}
	else
	{
		m_StartMove = 0;
	}
}

void Player::IsMoveStop()
{
	m_IsMove = false;
	m_StartMove = 0;

	if (m_pos.x < kFristPlayerPosX - 30)
	{
		m_StartMove = kStartMoveSpeed;
		m_pos.x += m_StartMove;
	}

	if (m_pos.x > kFristPlayerPosX + 30)
	{
		m_StartMove = -kStartMoveSpeed;
		m_pos.x += m_StartMove;
	}
}

void Player::Ondamage()
{
	m_Hp--;
}

void Player::IsKnockBack(Vec2 EnemyPos)
{
	Vec2 vel = m_pos - EnemyPos;

	vel = vel.normalize();
	vel *= m_KnockBack;
	m_KnockBack -= kKnockBackSpeedDown;
	if (m_KnockBack > 0)
	{
		m_pos += vel;
	}
}
