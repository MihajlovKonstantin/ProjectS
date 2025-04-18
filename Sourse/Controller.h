#pragma once
class Controller
{
	std::vector<int> m_input;
	std::vector<int> m_toDelete;
	bool m_dirty = false;
	bool b_w, b_a, b_s, b_d, b_up, b_down, b_left, b_right, b_lmb, b_rmb, b_e,b_tab;
public:
	void Init();
	bool GetDirty();
	void Update(bool blockInput = false);
	std::vector<int> GetData();
	void Clear();
public:
	static Controller& GetInstance()
	{
		static Controller instance;
		return instance;
	}
};
#define CONTROLLER Controller::GetInstance()
