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

	Block m_block;

	KdTexture m_PCTex;
public:
	
	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	void GameDraw();

	void PauseDraw();

	// GUIˆ—
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
