#pragma once
#include "LibList.h"
class Scene
{
	enum GameMode
	{
		Game = 1,
		Edit,
		Pause
	};
private:
	GameMode m_currentGM = Game, m_previousGM = m_currentGM;
	int m_gameModeColdown = 80, m_currentGMColdown = 0;
	int m_pauseCouldown = 60, m_currentPauseColdown = 0;

	PC m_player;

	std::vector<Block> m_block;

	KdTexture m_PCTex;
public:
	
	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	void GameDraw();

	void PauseDraw();

	// GUI処理
	void ImGuiUpdate();

	void GameSceneUpdate();

	void EditSceneUpdate();

	void PauseSceneUpdate();

	void GMUpdate();
private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
