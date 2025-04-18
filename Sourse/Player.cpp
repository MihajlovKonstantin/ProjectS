#include "Pch.h"
#include "Player.h"

Math::Matrix Player::GetMatrix() 
{
	return m_matrix;
}

KdTexture* Player::GetTexture() 
{
	return m_texture;
}

Math::Rectangle Player::GetRectangle() 
{
	return m_textureRectangle;
}

void Player::SetTexture(KdTexture* texture)
{
	m_texture = texture;
}

void Player::SetScroll(DirectX::XMFLOAT2* scroll)
{
	m_scroll = scroll;
}

void Player::Update() 
{
	if (m_moveDirty)
	{
		m_speed.x = m_speedBase.x * m_speedMod.x * m_speedDir.x;
		m_speed.y = m_speedBase.y * m_speedMod.y * m_speedDir.y;
	}
	
	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;

	m_rotateMat = Math::Matrix::CreateRotationZ(m_rotation);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_translateMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_matrix = m_scaleMat * m_rotateMat * m_translateMat;
}

void Player::Release()
{
}

DirectX::XMFLOAT2* Player::GetScroll()
{
	return m_scroll;
}
