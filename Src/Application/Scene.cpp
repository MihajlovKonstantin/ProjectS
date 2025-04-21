#include "main.h"
#include "Scene.h"
#include "Sourse/Controller.h"
void Scene::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_player.GetMatrix());
	SHADER.m_spriteShader.DrawTex(m_player.GetTexture(),Math::Rectangle(0,0,32,32));

	for each(Block var in m_block)
	{
		SHADER.m_spriteShader.SetMatrix(var.GetMatrix());
		SHADER.m_spriteShader.DrawTex(var.GetTexture(), var.GetRectangle());
	}
	
}

void Scene::Update()
{
	CONTROLLER.Update(false);
	GMUpdate();
	if (CONTROLLER.GetDirty())
	{
		switch (m_currentGM)
		{
		case Game:
			m_player.SetInput(CONTROLLER.GetData());
			break;
		}
		
	}
	for each(Block var in m_block)
	{
		m_player.CollisionToBlock(var);
	}
	
	switch (m_currentGM)
	{
	case Game:
		GameSceneUpdate();
		break;
	case Edit:
		EditSceneUpdate();
		break;
	case Pause:
		PauseSceneUpdate();
		break;
	}
	
	CONTROLLER.Clear();
}

void Scene::Init()
{
	m_PCTex.Load("Texture/Player/PC.png");
	m_player = PC(&m_PCTex, &APP.m_mouse);
	m_block.push_back ( Block({ 0,100,0 }, { 32,32 ,0}, m_player.GetScroll(), m_player.GetTexture(), 0, 0.0f));
	m_block.push_back(Block({ 32,100,0 }, { 32,32 ,0 }, m_player.GetScroll(), m_player.GetTexture(), 0, 0.0f));
}

void Scene::Release()
{
	m_PCTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::GameSceneUpdate()
{
	m_player.Update();
}

void Scene::EditSceneUpdate()
{
}

void Scene::PauseSceneUpdate()
{
}

void Scene::GMUpdate()
{
	auto _input = CONTROLLER.GetData();
	if (!_input.empty())
	{
		bool _change = false;
		auto _it = std::find(_input.begin(), _input.end(), ENUM::KeyIndex::E);
		if ((_it != _input.end())&&(m_currentGMColdown==0))
		{
			m_previousGM = m_currentGM;
			_change = false;
			(m_currentGM == Game) && (!_change) ? m_currentGM = Edit,_change = true : _change = false;
			(m_currentGM == Edit)&&(!_change) ? m_currentGM = Game : m_currentGM;
			!(m_previousGM == m_currentGM)?m_currentGMColdown=m_gameModeColdown:m_currentGMColdown;
		}

		_it = std::find(_input.begin(), _input.end(), ENUM::KeyIndex::Tab);
		if(_it!=_input.end()&&(m_currentPauseColdown==0))
		{
			m_currentGM != Pause ? m_previousGM = m_currentGM, m_currentGM = Pause : m_currentGM = m_previousGM;
			m_currentPauseColdown = m_pauseCouldown;
		}
	}
	
	m_currentGMColdown > 0 ? m_currentGMColdown-- : m_currentGMColdown;
	m_currentPauseColdown > 0 ? m_currentPauseColdown-- : m_currentPauseColdown;
}
