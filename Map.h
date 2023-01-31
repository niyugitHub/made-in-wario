#pragma once
#include "game.h"
#include "Vec2.h"

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

	public:
		Map();
		~Map();

		Vec2 GetPos() { return m_LeftPos; }
		Vec2 GetVec() { return m_ScrollSpeed; }

		// 当たり判定をセット
		void SetCollRight(bool Right) { m_CollRight = Right; }
		void SetCollLeft(bool Left) { m_CollLeft = Left; }

		// グラフィックのロード、アンロード
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update();

		// 描画
		void draw();
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

		// グラフィックのデータ
		int m_graphWidth;
		int m_graphHeight;

		//左端のマップの番号
		int m_LeftNum;

		//右端のマップの番号
		int m_RightNum;

		// マップの左端の座標
		Vec2 m_LeftPos;

		// マップの右端の座標
		Vec2 m_RightPos;

		// スクロールのスピード
		Vec2 m_ScrollSpeed;

		// ベクトル
		Vec2 m_Vec;
};

