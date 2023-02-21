#pragma once
#include "game.h"
#include "Vec2.h"
#include <memory>

class Map
{
	public:
		// マップチップの１つのサイズ
		static constexpr int kChipSize = 64;

		// チップの数
		static constexpr int kBgNumY = 17;
		static constexpr int kBgNumX = 150;

		// 一画面に表示できるマップチップの数
		static constexpr int kChipNumY = 17;
		static constexpr int kChipNumX = 30;

		// マップチップ分割数
		static constexpr int kChipDivisionX = 16;
		static constexpr int kChipDivisionY = 16;

		//	Platinumで分けたマップチップの横一列の数
		static constexpr int kSideMapChipNum = 16;

	public:
		Map();
		~Map();

	/*	void setPlayer(std::shared_ptr<Player> pPlayer) { m_player = pPlayer; }*/

		Vec2 GetPos() { return m_Pos; }
		Vec2 GetVec() { return m_ScrollSpeed; }

		int GetPosX() { return m_Pos.x; }

		void SetMap(Vec2 Pos) { m_Pos = Pos; }

		// ステージの番号を取得
		int GetStageNum() { return m_StageNum; }

		// 当たり判定をセット
		void SetCollRight(bool Right) { m_CollRight = Right; }
		void SetCollLeft(bool Left) { m_CollLeft = Left; }

		// グラフィックのロード、アンロード
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update(Vec2 offset);

		// 描画
		void draw();

		// プレイヤーの向きとノックバックの移動量
		void PlayerMove(float knockback, float Move);

		// マップの番号変更
		void SetStage();

		// 広さを取得
		int getWidth() const;
		int getHeight() const;
	private:
		// マップチップの数を取得する
		int chipNumX();
		int chipNumY();
		int chipNum();

	private:
		// マップの描画
		void drawMap();

		// 当たり判定
		bool m_CollLeft;
		bool m_CollRight;

		// グラフィックデータのハンドル
		int m_handle;

		// グラフィックデータの配列
		int m_MapData[kBgNumY][kBgNumX];

		// ステージ番号
		int m_StageNum;

		// グラフィックのデータ
		int m_graphWidth;
		int m_graphHeight;

		//左端のマップの番号
		int m_LeftNum;

		//右端のマップの番号
		int m_RightNum;

		// マップの左端の座標
		Vec2 m_Pos;

		// スクロールのスピード
		Vec2 m_ScrollSpeed;

		// ベクトル
		Vec2 m_Vec;
};

