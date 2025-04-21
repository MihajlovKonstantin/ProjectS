#include "Pch.h"
#include "Sourse/Controller.h"

void Controller::Init()
{

}

bool Controller::GetDirty()
{
	return m_dirty;
}

void Controller::Update(bool blockInput)
{
	if (GetAsyncKeyState('W'))
	{
		if (!b_w)
		{
			b_w = true;
			m_input.push_back(ENUM::KeyIndex::W);
			m_dirty = true;
		}
	}
	else
	{
		if (b_w)
		{
			b_w = false;
			m_toDelete.push_back(ENUM::KeyIndex::W);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState('S'))
	{
		if (!b_s)
		{
			b_s = true;
			m_input.push_back(ENUM::KeyIndex::S);
			m_dirty = true;
		}
	}
	else
	{
		if (b_s)
		{
			b_s = false;
			m_toDelete.push_back(ENUM::KeyIndex::S);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState('A'))
	{
		if (!b_a)
		{
			b_a = true;
			m_input.push_back(ENUM::KeyIndex::A);
			m_dirty = true;
		}
	}
	else
	{
		if (b_a)
		{
			b_a = false;
			m_toDelete.push_back(ENUM::KeyIndex::A);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState('D'))
	{
		if (!b_d)
		{
			b_d = true;
			m_input.push_back(ENUM::KeyIndex::D);
			m_dirty = true;
		}
	}
	else
	{
		if (b_d)
		{
			b_d = false;
			m_toDelete.push_back(ENUM::KeyIndex::D);
			m_dirty = true;
		}

	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (!b_up)
		{
			b_up = true;
			m_input.push_back(ENUM::KeyIndex::UP);
			m_dirty = true;
		}
	}
	else
	{
		if (b_up)
		{
			b_up = false;
			m_toDelete.push_back(ENUM::KeyIndex::UP);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (!b_down)
		{
			b_down = true;
			m_input.push_back(ENUM::KeyIndex::DOWN);
			m_dirty = true;
		}
	}
	else
	{
		if (b_down)
		{
			b_down = false;
			m_toDelete.push_back(ENUM::KeyIndex::DOWN);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!b_left)
		{
			b_left = true;
			m_input.push_back(ENUM::KeyIndex::LEFT);
			m_dirty = true;
		}
	}
	else
	{
		if (b_left)
		{
			b_left = false;
			m_toDelete.push_back(ENUM::KeyIndex::LEFT);
			m_dirty = true;
		}

	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!b_right)
		{
			b_right = true;
			m_input.push_back(ENUM::KeyIndex::RIGHT);
			m_dirty = true;
		}
	}
	else
	{
		if (b_right)
		{
			b_right = false;
			m_toDelete.push_back(ENUM::KeyIndex::RIGHT);
			m_dirty = true;
		}
	}
	if (GetAsyncKeyState(VK_TAB))
	{
		if (!b_tab)
		{
			b_tab = true;
			m_input.push_back(ENUM::KeyIndex::Tab);
			m_dirty = true;
		}
	}
	else
	{
		if (b_tab)
		{
			b_tab = false;
			m_toDelete.push_back(ENUM::KeyIndex::Tab);
			m_dirty = true;
		}
	}
	if (GetAsyncKeyState('E'))
	{
		if (!b_e)
		{
			b_e = true;
			m_input.push_back(ENUM::KeyIndex::E);
			m_dirty = true;
		}
	}
	else
	{
		if (b_e)
		{
			b_e = false;
			m_toDelete.push_back(ENUM::KeyIndex::E);
			m_dirty = true;
		}
	}

	if (m_dirty&&(!m_toDelete.empty()))
	{
		do
		{
			int _toDelete = m_toDelete.back();
			m_toDelete.pop_back();
			auto _it = std::find(m_input.begin(), m_input.end(), _toDelete);
			if (_it != m_input.end())
			{
				m_input.erase(_it);
			}
		} while (!m_toDelete.empty());
	}
}

std::vector<int> Controller::GetData()
{
	return m_input;
}

void Controller::Clear()
{
	m_dirty = false;
}
