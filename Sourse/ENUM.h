#pragma once
class ENUM
{
public:
	enum WindowsIndex
	{
		Title = 1,
		MainMenu,
		PlayebleMapSelect,
		CreateMapSelect,
		Game,
		Setting
	};
	enum KeyIndex
	{
		W = 1,A,S,D,
		UP,DOWN,LEFT,RIGHT,
		LeftMouseButton, RightMouseButton,
		E,Tab
	};
};
struct DirectionMove
{
    bool s_right = false;
    bool s_left = false;
    bool s_up = false;
    bool s_down = false;
};
struct DirectionLook
{
    bool s_right = false;
    bool s_left = false;
    bool s_up = false;
    bool s_down = false;
};

