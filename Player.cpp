#include "Player.h"
#include "SceneTitle.h"
#include <DxLib.h>
#include <cassert>
#include"game.h"
#include"Pad.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";

	// フレームタイム
	constexpr int kFrameTime = 20;

	constexpr float kBigGravity = 1.2f;
	constexpr float kSmallGravity = 0.5f;
}

Player::Player() :
m_pos(0, 500),
m_vec(3, 0),
m_Jump(15.0f),
m_CharaGraphX(0),
m_CharaGraphY(0),
m_FrameChangeChara(0),
m_CharaMotion(0),
m_NowDash(false),
m_LookLeft(false),
m_NowJump(false),
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
	CharaMove();

	LimitMove();
}

void Player::draw()
{
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

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

	if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	{
		m_NowDash = true;
		m_LookLeft = false;
		m_CharaGraphY = 3;
		m_pos.x += m_vec.x * 2;
		m_CharaMotion = 8;
	}

	else if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	{
		m_NowDash = true;
		m_LookLeft = true;
		m_CharaGraphY = 3;
		m_pos.x -= m_vec.x * 2;
		m_CharaMotion = 8;
	}

	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_LookLeft = false;
		m_CharaGraphY = 2;
		m_pos.x += m_vec.x;
		m_CharaMotion = 4;
	}

	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_LookLeft = true;
		m_CharaGraphY = 2;
		m_pos.x -= m_vec.x;
		m_CharaMotion = 4;
	}

	else
	{
		m_CharaGraphY = 0;
		m_CharaMotion = 2;
	}

	if (Pad::isTrigger(PAD_INPUT_10))
	{
		m_NowJump = true;
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
			m_FrameChangeChara++;
			m_CharaGraphY = 6;
		}
	}

	m_FrameChangeChara++;

	if (m_NowDash)
	{
		m_FrameChangeChara += 3;
	}

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
	m_FrameChangeChara++;
	m_CharaGraphY = 5;
	m_CharaMotion = 8;
	m_pos.y -= m_Jump;

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_Jump -= kSmallGravity;
	}
	else
	{
		m_Jump -= kBigGravity;
	}

	if (m_pos.y >= Game::kScreenHeight - kColumnSize)
	{
		m_NowJump = false;
	//	m_pos.y = Game::kScreenHeight - kColumnSize;
		m_Jump = 15;
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
	if (m_pos.y > Game::kScreenHeight - kColumnSize)
	{
		m_pos.y = Game::kScreenHeight - kColumnSize;
	}
}
