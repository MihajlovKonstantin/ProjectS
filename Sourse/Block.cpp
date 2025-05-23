#include "Pch.h"
#include "Sourse/Block.h"

void Block::SetScroll(DirectX::XMFLOAT3* scroll)
{
	m_scroll = scroll;
}

void Block::SetPos(DirectX::XMFLOAT3 pos)
{
	m_globalPos = pos;
}

void Block::SetSize(DirectX::XMFLOAT3 size)
{
	m_size.x = size.x/2;
	m_size.y = size.y / 2;
	m_size.z = size.z;
}

void Block::SetTexture(KdTexture* texture)
{
	m_texture = texture;
}

void Block::SetBackStage(int backStage)
{
	m_backStage = backStage;
}

void Block::SetRotation(float rotation)
{
	m_rotation = rotation;
}

Math::Matrix Block::GetMatrix()
{
	return m_matrix;
}

Math::Rectangle Block::GetRectangle()
{
	return m_rectangle;
}

bool Block::GetBackStage()
{
	return m_backStage;
}

float Block::GetRotation()
{
	return m_rotation;
}

DirectX::XMFLOAT3 Block::GetGlobalPos()
{
	return m_globalPos;
}

KdTexture* Block::GetTexture()
{
	return m_texture;
}

DirectX::BoundingOrientedBox Block::GetBox()
{
	return m_box;
}

void Block::SetDeleteState()
{
	m_deleteState = true;
}

Block::Block()
{
}

Block::Block(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3* scroll, KdTexture* texture, int backStage, float rotation)
{
	SetPos(pos);
	SetSize(size);
	SetScroll(scroll);
	SetTexture(texture);
	SetBackStage(backStage);
	SetRotation(rotation);

	m_matrix =Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotation))* Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	m_rectangle = Math::Rectangle(0,0,long(size.x),long( size.y));

	m_box = DirectX::BoundingOrientedBox(pos, m_size, DirectX::XMFLOAT4(0, 0, 0, 1));
	DirectX::XMVECTOR _rotationVector = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMConvertToRadians(rotation));
	DirectX::XMStoreFloat4(&m_box.Orientation, _rotationVector);
}
