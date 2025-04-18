#include "Pch.h"
#include "PC.h"

void PC::GetMoveStatus(DirectionMove moveDir)
{
	m_speedDir = { 0,0 };
	
	moveDir.s_left ? m_speedDir.x--:m_speedDir.x;
	moveDir.s_right ? m_speedDir.x++ : m_speedDir.y;

	moveDir.s_up ? m_speedDir.y++ : m_speedDir.y;
	moveDir.s_down ? m_speedDir.y-- : m_speedDir.y;
	m_moveDirty = true;
}

void PC::SetInput(std::vector<int> input)
{
	m_moveDir = DirectionMove();
	for (size_t i = 0; i < input.size();i++)
	{
		switch (input.at(i))
		{
		case ENUM::KeyIndex::W:
			m_moveDir.s_up = true;
			break;
		case ENUM::KeyIndex::S:
			m_moveDir.s_down = true;
			break;
		case ENUM::KeyIndex::A:
			m_moveDir.s_left = true;
			break;
		case ENUM::KeyIndex::D:
			m_moveDir.s_right = true;
			break;
		}
	}
	m_moveDirty = true;
}

void PC::Update()
{
	GetMoveStatus(m_moveDir);
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
