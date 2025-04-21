#include "Pch.h"
#include "PC.h"

bool PC::CalculateMoveState()
{
	bool _result = true;
	m_speedDir = { 0,0,0 };
	m_implacatedMove = stand;
	EliminateOppositeInput();
	
	ImplicateInput();

	float _angleSpeedMod = cos(DirectX::XMConvertToRadians(45.0f));

	switch (m_implacatedMove)
	{
	case up:
		m_speedDir.y++;
		break;
	case down:
		m_speedDir.y--;
		break;
	case left:
		m_speedDir.x--;
		break;
	case right:
		m_speedDir.x++;
		break;

	case up_l:
		m_speedDir.x = (-(_angleSpeedMod));
		m_speedDir.y = (_angleSpeedMod);
		break;
	case up_r:
		m_speedDir.x = (_angleSpeedMod);
		m_speedDir.y = (_angleSpeedMod);
		break;
	case down_l:
		m_speedDir.x = (-(_angleSpeedMod));
		m_speedDir.y = ( -(_angleSpeedMod));
		break;
	case down_r:
		m_speedDir.x = (_angleSpeedMod);
		m_speedDir.y = (-(_angleSpeedMod));
		break;
	}

	m_moveDirty = true;
	return _result;
}

void PC::ImplicateInput()
{
	if (m_moveDirInput.s_up)
	{
		if (m_moveDirInput.s_left)
		{
			if (!m_moveBlock.s_up_l)
			{
				m_implacatedMove=up_l;
			}
			else
			{
				if (m_moveBlock.s_left)
				{
					if((!m_moveBlock.s_up)) m_implacatedMove=up;
				}
				else
				{
					 m_implacatedMove=left;
				}
			}
		}

		if (m_moveDirInput.s_right)
		{
			if (!m_moveBlock.s_up_r)
			{
				m_implacatedMove=up_r;
			}
			else
			{
				if (m_moveBlock.s_right)
				{
					if ((!m_moveBlock.s_up)) m_implacatedMove = up;
				}
				else
				{
					m_implacatedMove=right;
				}
			}
		}
		if ((!m_moveDirInput.s_right) && (!m_moveDirInput.s_left) && (!m_moveBlock.s_up))
		{
			m_implacatedMove = up;
		}

	}

	if (m_moveDirInput.s_down)
	{
		if (m_moveDirInput.s_left)
		{
			if (!m_moveBlock.s_down_l)
			{
				m_implacatedMove=down_l;
			}
			else
			{
				if (m_moveBlock.s_left)
				{
					if ((!m_moveBlock.s_down)) m_implacatedMove = down;
				}
				else
				{
					m_implacatedMove=left;
				}
			}
		}

		if (m_moveDirInput.s_right)
		{
			if (!m_moveBlock.s_down_r)
			{
				m_implacatedMove=down_r;
			}
			else
			{
				if (m_moveBlock.s_right)
				{
					if ((!m_moveBlock.s_down)) m_implacatedMove = down;
				}
				else
				{
					m_implacatedMove=right;
				}
			}
		}
		if ((!m_moveDirInput.s_right) && (!m_moveDirInput.s_left) && (!m_moveBlock.s_down))
		{
			m_implacatedMove = down;
		}

	}

	if ((!m_moveDirInput.s_up) && (!m_moveDirInput.s_down))
	{
		if (m_moveDirInput.s_left && (!m_moveBlock.s_left))
		{
			m_implacatedMove=left;
		}

		if (m_moveDirInput.s_right && (!m_moveBlock.s_right))
		{
			m_implacatedMove=right;
		}
	}
}

void PC::EliminateOppositeInput()
{
	if (m_moveDirInput.s_left && m_moveDirInput.s_right)
	{
		m_moveDirInput.s_left = false;
		m_moveDirInput.s_right = false;
	}
	if (m_moveDirInput.s_up && m_moveDirInput.s_down)
	{
		m_moveDirInput.s_up = false;
		m_moveDirInput.s_down = false;
	}
}

void PC::SetInput(std::vector<int> input)
{
	m_moveDirInput = DirectionMove();
	for (size_t i = 0; i < input.size();i++)
	{
		switch (input.at(i))
		{
		case ENUM::KeyIndex::W:
			m_moveDirInput.s_up = true;
			break;
		case ENUM::KeyIndex::S:
			m_moveDirInput.s_down = true;
			break;
		case ENUM::KeyIndex::A:
			m_moveDirInput.s_left = true;
			break;
		case ENUM::KeyIndex::D:
			m_moveDirInput.s_right = true;
			break;
		}
	}
	m_moveDirty = true;
}

void PC::Update()
{
	CalculatePossibleDirectionToMove();
	CalculateMoveState();
	m_rotation = CalculateView();
	Player::Update();
	m_moveDirty = false;
}

void PC::SetMouse(POINT* mouse)
{
	m_mouse = mouse;
}

float PC::CalculateView()
{
	return std::atan2(m_mouse->y - m_pos.y, m_mouse->x - m_pos.x);
}

PC::PC(KdTexture* texture, POINT* mouse)
{
	SetTexture(texture);
	SetMouse(mouse);

	m_sphere = DirectX::BoundingSphere({ m_pos.x,m_pos.y,0 }, 16.0f);
}

PC::PC()
{
}
