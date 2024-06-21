#pragma once
#include "../D2DEngine/D2DEngine.h"
#include "ECSCall.h"
#include "Rectangle.h"

class EventHandler;

class DemoApp : public WinApp
{
public:
	DemoApp() = default;
	~DemoApp() = default;

	virtual void Initialize(HINSTANCE _hInstance) override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual void Finalize() override;



private:
	
};
	
