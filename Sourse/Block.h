#pragma once
class Block
{
	DirectX::XMFLOAT2 _scroll;
	DirectX::XMFLOAT2* m_scroll = &_scroll;

	DirectX::XMFLOAT2 m_globalPos;
	DirectX::XMFLOAT2 m_localPos;

	DirectX::XMFLOAT2 m_size = { 32,32 };
	KdTexture* m_texture;
	Math::Matrix m_transMat, m_rotateMat, m_matrix;
	Math::Rectangle m_rectangle;
	
	bool m_backStage = false;

	float m_rotation = 0;
	bool m_deleteState = false;

	DirectX::BoundingOrientedBox m_box;

private:
	void SetScroll(DirectX::XMFLOAT2* scroll);
	void SetPos(DirectX::XMFLOAT2 pos);
	void SetSize(DirectX::XMFLOAT2 size);
	void SetTexture(KdTexture* texture);
	void SetBackStage(int backStage);
	void SetRotation(float rotation);
public:
	Math::Matrix GetMatrix();
	Math::Rectangle GetRectangle();

	bool GetBackStage();
	float GetRotation();
	DirectX::XMFLOAT2 GetGlobalPos();
	KdTexture* GetTexture();

	void SetDeleteState();
	Block();
	Block(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, DirectX::XMFLOAT2* scroll, KdTexture* texture, int backStage, float rotation);
};

