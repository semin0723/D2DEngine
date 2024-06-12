#pragma once

class Component
{
public:
	Component() {}
	~Component() {}

	void SetEnable(const bool _state) { enable = _state; }
	const bool GetEnable() const { return enable; }
private:
	bool enable = true;
};

