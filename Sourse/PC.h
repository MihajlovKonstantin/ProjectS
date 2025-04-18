#pragma once
#include "Sourse/Player.h"
class PC :
    public Player
{
    DirectionMove m_moveDir;
    POINT* m_mouse;
public:
    void GetMoveStatus(DirectionMove moveDir);
    void SetInput(std::vector<int> input);
    void Update();
    void SetMouse(POINT* mouse);
    float CalculateView();
};

