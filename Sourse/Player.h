#pragma once
#include "Sourse/Block.h"
class Player
{
protected:
    
    struct CollisionEffect
    {
        bool s_backStage;
    };
    struct CollisionBlockData
    {
        float s_rad;
        float s_pos;
        CollisionEffect s_collisionEffect;
    };
    struct DirectionMoveExpandStruct
    {
        bool s_up = false, s_up_r = false, s_right = false, s_down_r = false;
        bool s_down = false, s_down_l = false, s_left = false, s_up_l = false;
    };
    enum DirectionMoveExpandEnum
    {
        stand = 0,
         up = 1, up_r, right, down_r,
         down, down_l, left, up_l
    };

    DirectionMove m_moveDirInput;
    DirectionMoveExpandStruct m_moveBlock;
    DirectionMoveExpandEnum m_implacatedMove;
    DirectX::XMFLOAT3 m_pos = { 0,0,0 };
    DirectX::XMFLOAT3 _scroll = { 0,0,0 };
    DirectX::XMFLOAT3* m_scroll = &_scroll;
    float m_rotation = 0;
    float m_scale = 1;
    DirectX::XMFLOAT3 m_size = {32,32,0};
    DirectX::XMFLOAT3 m_speedBase = { 3,3,0 };
    DirectX::XMFLOAT3 m_speedMod = { 1,1,1 };
    DirectX::XMFLOAT3 m_speedDir;
    DirectX::XMFLOAT3 m_speed;


    float m_HP = 100;
    float m_maxHP = 100;

    KdTexture* m_texture;
    KdTexture* m_HPBarTexture;
    Math::Rectangle m_textureRectangle;
    Math::Rectangle m_barRectangle;
    DirectX::BoundingSphere m_sphere;

    Math::Matrix m_scaleMat, m_rotateMat, m_translateMat;
    Math::Matrix m_matrix;

    bool m_moveDirty = false;
protected:
    void CalculatePossibleDirectionToMove();
public:
    Math::Matrix GetMatrix();
    KdTexture* GetTexture();
    Math::Rectangle GetRectangle();

    void SetTexture(KdTexture* texture);
    void SetScroll(DirectX::XMFLOAT3* scroll);

    void Update();
    void Release();
    DirectX::XMFLOAT3* GetScroll();
    void CollisionToBlock(Block block);
    ~Player() = default;
   
};

