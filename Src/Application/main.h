#pragma once

class Application
{
public:

	void Execute();

	void End() { m_endFlag = true; }


	KdGameWindow		m_window;

	int				m_fps = 0;					
	int				m_maxFps = 60;				

	POINT m_mouse;
	POINT m_mouseScroll;



private:

	bool Init(int w, int h);

	void Release();

	bool		m_endFlag = false;


private:
	// 
	Application() {}

public:
	static Application &GetInstance(){
		static Application Instance;
		return Instance;
	}
};

#define APP Application::GetInstance()
