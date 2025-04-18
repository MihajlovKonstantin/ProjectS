#include "main.h"
#include "Sourse/Controller.h"
#include "Scene.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	setlocale(LC_ALL, "japanese");

	APP.Execute();

	CoUninitialize();

	return 0;
}



bool Application::Init(int w, int h)
{
	if (m_window.Create(w, h, "DirectX", "Window") == false) {
		MessageBoxA(nullptr, "ウィンドウ作成に失敗", "エラー", MB_OK);
		return false;
	}

	bool bFullScreen = false;
	/*if (MessageBoxA(m_window.GetWndHandle(), "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}*/

	bool deviceDebugMode = false;
	#ifdef _DEBUG
	deviceDebugMode = true;
	#endif

	std::string errorMsg;
	if (D3D.Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	if (bFullScreen) {
		D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	}

	SHADER.Init();

	if (AUDIO.Init() == false)
	{
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "サウンド初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(m_window.GetWndHandle());
	ImGui_ImplDX11_Init(D3D.GetDev(), D3D.GetDevContext());

	{
		// 日本語対応
		#include "imgui/ja_glyph_ranges.h"
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);
	}
	CONTROLLER.Init();
	return true;
}

void Application::Release()
{
	D3D.GetSwapChain()->SetFullscreenState(FALSE, 0);

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SHADER.Release();

	D3D.Release();

	AUDIO.Release();

	m_window.Release();

}

// アプリケーション実行
void Application::Execute()
{
	if (APP.Init(1280, 720) == false) {
		return;
	}

	SCENE.Init();

	// 時間
	DWORD baseTime = timeGetTime();
	int count = 0;
	
	// ループ
	while (1)
	{
		GetCursorPos(&m_mouse);
		ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse);
		m_mouse.x -= 640;
		m_mouse.y = -m_mouse.y + 360;

		DWORD st = timeGetTime();

		if (m_endFlag)
		{ 
			break;
		}
		m_window.ProcessMessage();

		if (m_window.IsCreated() == false)
		{
			break;
		}

		AUDIO.Update();


		// バックバッファクリア
		D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer(), Math::Color(0.3f, 0.3f, 0.5f, 1));
		// Zバッファクリア
		D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

		SCENE.Update();

		SHADER.m_spriteShader.Begin();
		SCENE.Draw2D();
		SHADER.m_spriteShader.End();
		
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		SCENE.ImGuiUpdate();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		D3D.GetSwapChain()->Present(0, 0);


		DWORD et = timeGetTime();
		DWORD ms = 1000 / m_maxFps;
		if (et - st < ms)
		{
			Sleep(ms - (et - st));	
		}

		count++;
		if (st - baseTime >= 1000)
		{
			m_fps = (count * 1000) / (st - baseTime);
			baseTime = st;
			count = 0;
		}

	}

	SCENE.Release();

	Release();
}