#include "Player.h"
#include <DxLib.h>
#include <cassert>
#include"game.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";

	// フレームタイム
	constexpr int kFrameTime = 20;

	constexpr int kGravity = 0.4;
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
m_LookLeft(false)
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
	LoadDivGraph(kPlayerGraphicFilename, kSideCharaChipNum * kColumnCharaChipNum,
		kSideCharaChipNum, kColumnCharaChipNum,
		kSideSize, kColumnSize, m_handle);	
}

void Player::end()
{
}

void Player::update()
{
	CharaMove();
}

void Player::draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

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

	if (CheckHitKey(KEY_INPUT_LEFT))
	{

	}
	CharaJump();

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
	m_CharaGraphY = 5;
	m_CharaMotion = 8;
	m_pos.y -= m_Jump;
	m_Jump -= kGravity;

	if (m_pos.y >= 500)
	{
		m_pos.y = 500;
		m_Jump = 15;
	}
}
