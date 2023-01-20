#pragma once
#include "game.h"

class Minigame1
{
	public:
		// マップチップの１つのサイズ
		static constexpr int kChipSize = 64;

		// チップの数
		static constexpr int kBgNumY = 17;
		static constexpr int kBgNumX = 30;

	public:
		Minigame1();
		~Minigame1();

		// グラフィックのロード、アンロード
		void load();
		void unload();

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

		// グラフィックデータのハンドル
		int m_handle;

		// グラフィックのデータ
		int m_graphWidth;
		int m_graphHeight;
};

