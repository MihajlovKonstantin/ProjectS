#pragma once
class Block
{
	DirectX::XMFLOAT3 _scroll;
	DirectX::XMFLOAT3* m_scroll = &_scroll;

	DirectX::XMFLOAT3 m_globalPos;
	DirectX::XMFLOAT3 m_localPos;

	DirectX::XMFLOAT3 m_size;
	KdTexture* m_texture;
	Math::Matrix m_transMat, m_rotateMat, m_matrix;
	Math::Rectangle m_rectangle;
	
	bool m_backStage = false;

	float m_rotation = 0;
	bool m_deleteState = false;

	DirectX::BoundingOrientedBox m_box;

private:
	void SetScroll(DirectX::XMFLOAT3* scroll);
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);
	void SetTexture(KdTexture* texture);
	void SetBackStage(int backStage);
	void SetRotation(float rotation);
public:
	Math::Matrix GetMatrix();
	Math::Rectangle GetRectangle();

	bool GetBackStage();
	float GetRotation();
	DirectX::XMFLOAT3 GetGlobalPos();
	KdTexture* GetTexture();
	DirectX::BoundingOrientedBox GetBox();

	void SetDeleteState();
	Block();
	Block(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3* scroll, KdTexture* texture, int backStage, float rotation);
};

