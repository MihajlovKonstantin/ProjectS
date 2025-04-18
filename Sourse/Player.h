#pragma once
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

    DirectX::XMFLOAT2 m_pos;
    DirectX::XMFLOAT2 _scroll = { 0,0 };
    DirectX::XMFLOAT2* m_scroll = &_scroll;
    float m_rotation = 0;
    float m_scale = 1;
    DirectX::XMFLOAT2 m_speedBase = { 10,10 };
    DirectX::XMFLOAT2 m_speedMod = { 1,1 };
    DirectX::XMFLOAT2 m_speedDir;
    DirectX::XMFLOAT2 m_speed;

    float m_HP = 100;
    float m_maxHP = 100;

    KdTexture* m_texture;
    KdTexture* m_HPBarTexture;
    Math::Rectangle m_textureRectangle;
    Math::Rectangle m_barRectangle;

    Math::Matrix m_scaleMat, m_rotateMat, m_translateMat;
    Math::Matrix m_matrix;

    bool m_moveDirty = false;
public:
    Math::Matrix GetMatrix();
    KdTexture* GetTexture();
    Math::Rectangle GetRectangle();

    void SetTexture(KdTexture* texture);
    void SetScroll(DirectX::XMFLOAT2* scroll);

    void Update();
    void Release();
    DirectX::XMFLOAT2* GetScroll();
     ~Player() = default;
};

