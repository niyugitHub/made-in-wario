#pragma once
#include "game.h"
#include "Vec2.h"
#include<vector>
#include <memory>

class MapGimmick;

class Map
{
	public:
		// マップチップの１つのサイズ
		static constexpr float kChipSize = 64;

		// チップの数
		static constexpr int kBgNumY[5] = { 20,17,17,17,17 };
		static constexpr int kBgNumX[5] = { 150,150,150,150,150 };

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

		// ギミックの座標取得
		Vec2 GetGimmickPos(int i);
		// ギミックの個数取得
		int GetGimmickCount() { return m_GimmickCount; }

		void SetMap(Vec2 Pos) { m_Pos = Pos; }

		// ステージの番号を取得
		int GetStageNum() { return m_StageNum; }

		// 当たり判定をセット
		void SetCollRight(bool Right) { m_CollRight = Right; }
		void SetCollLeft(bool Left) { m_CollLeft = Left; }

		// マップ初期化
		void Init();

		// グラフィックのロード、アンロード
		void load();
		void unload();

		int GetMapData(int Y, int X) { return m_MapData[Y][X]; }

		void update();

		// 描画
		void draw(Vec2 offset);

		// プレイヤーの向きとノックバックの移動量
		void PlayerMove(float knockback, float Move);

		// マップの番号変更
		void SetStage();

		// 広さを取得
		int getWidth() const;
		int getHeight() const;

		void SetPlayerPos(Vec2 PlayerPos) { m_PlayerPos = PlayerPos; }
	private:
		// マップチップの数を取得する
		int chipNumX();
		int chipNumY();
		int chipNum();

	private:
		// マップの描画
		void drawMap(Vec2 offset);

		// 当たり判定
		bool m_CollLeft;
		bool m_CollRight;

		// プレイヤーの座標取得
		Vec2 m_PlayerPos;

		// 背景の座標取得
		Vec2 m_BackGroundPos;

		// グラフィックデータのハンドル
		int m_handle;
		// ギミックのハンドル
		int m_GimmickHandle;
		// 背景のハンドル
		int m_BackGroundHandle[5];

		// グラフィックデータの配列
		int m_MapData[50][500];

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

		// ギミックの個数
		int m_GimmickCount;

		// ギミック
		std::vector<std::shared_ptr<MapGimmick>> m_Gimmick;
};

