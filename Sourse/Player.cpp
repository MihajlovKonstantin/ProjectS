#include "Pch.h"
#include "Player.h"

void Player::CalculatePossibleDirectionToMove()
{
	if (m_moveBlock.s_up && m_moveBlock.s_left)
	{
		m_moveBlock.s_up_l = true;
	}
	if (m_moveBlock.s_up && m_moveBlock.s_right)
	{
		m_moveBlock.s_right = true;
	}
	if (m_moveBlock.s_down && m_moveBlock.s_left)
	{
		m_moveBlock.s_down_l = true;
	}
	if (m_moveBlock.s_down && m_moveBlock.s_right)
	{
		m_moveBlock.s_down_r = true;
	}

}

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

void Player::SetScroll(DirectX::XMFLOAT3* scroll)
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
	m_sphere.Center.x += m_speed.x;
	m_sphere.Center.y += m_speed.y;

	m_rotateMat = Math::Matrix::CreateRotationZ(m_rotation);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_translateMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_matrix = m_scaleMat * m_rotateMat * m_translateMat;
	m_moveBlock = DirectionMoveExpandStruct();
}

void Player::Release()
{
}

DirectX::XMFLOAT3* Player::GetScroll()
{
	return m_scroll;
}

void Player::CollisionToBlock(Block block)
{
	auto _blockBox = block.GetBox();

	bool _intersectResult = _blockBox.Intersects(m_sphere);

	if (_intersectResult)
	{	
		float _degree = 0;
		DirectX::XMFLOAT2 _centerDelta = { m_pos.x - _blockBox.Center.x,m_pos.y - _blockBox.Center.y };
		DirectX::XMFLOAT2 _collisionDistance = { m_size.x / 2 + _blockBox.Extents.x ,m_size.y / 2 + _blockBox.Extents.y };

		if (block.GetRotation() == 0)
		{
			if (abs(_centerDelta.x) <= (_collisionDistance.x))
			{
				if (_centerDelta.x > 0)
				{
					m_moveBlock.s_left = true;
					m_moveBlock.s_up_l = true;
					m_moveBlock.s_down_l = true;
					if ((_centerDelta.x < _collisionDistance.x)&&(abs(_centerDelta.x)>=abs(_centerDelta.y)))
					{
							m_pos.x += _collisionDistance.x - _centerDelta.x;
						
					}
				}
				else 
				{
					m_moveBlock.s_right = true;
					m_moveBlock.s_up_r = true;
					m_moveBlock.s_down_r = true;
					if ((_centerDelta.x > -_collisionDistance.x) && (abs(_centerDelta.x) >= abs(_centerDelta.y)))
					{
						m_pos.x += -_collisionDistance.x - _centerDelta.x;

					}
				}
			}
			if (abs(_centerDelta.y) <= (_collisionDistance.y))
			{
				if (_centerDelta.y > 0)
				{
					m_moveBlock.s_down = true;
					m_moveBlock.s_down_l = true;
					m_moveBlock.s_down_r = true;
					if ((_centerDelta.y > -_collisionDistance.y) && (abs(_centerDelta.y) >= abs(_centerDelta.x)))
					{
						m_pos.y += _collisionDistance.y - _centerDelta.y;

					}
				}
				else
				{
					m_moveBlock.s_up = true;
					m_moveBlock.s_up_l = true;
					m_moveBlock.s_up_r = true;
					if ((_centerDelta.y > -_collisionDistance.y) && (abs(_centerDelta.y) >= abs(_centerDelta.x)))
					{
						m_pos.y += -_collisionDistance.y - _centerDelta.y;

					}
				}
			}
		}
		else
		{
			if ((_centerDelta.x >= 0) && (_centerDelta.y >= 0))
			{
				m_moveBlock.s_left = true;
				m_moveBlock.s_down_l = true;
				m_moveBlock.s_down = true;
			}
			if ((_centerDelta.x <= 0) && (_centerDelta.y >= 0))
			{
				m_moveBlock.s_right = true;
				m_moveBlock.s_down_r= true;
				m_moveBlock.s_down = true;
			}
		}
		m_sphere.Center.x = m_pos.x;
		m_sphere.Center.y = m_pos.y;
	}
}
