#pragma once
#include "Sourse/Player.h"
class PC :
    public Player
{
  
    POINT* m_mouse;
private:
    float CalculateView();
    bool CalculateMoveState();
    void ImplicateInput();
    void EliminateOppositeInput();
public:
    
    void SetInput(std::vector<int> input);
    void Update();
    void SetMouse(POINT* mouse);
    
    PC(KdTexture* texture, POINT* mouse);
    PC();
};

