#pragma once
#include "../D2DEngine/D2DEngine.h"
#include "RenderComponent.h"

class DemoApp : public WinApp
{
public:
	DemoApp() = default;
	~DemoApp() = default;

	virtual void Initialize(HINSTANCE _hInstance) override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void Finalize() override;

private:
	RenderComponent _renderComponent;

};

