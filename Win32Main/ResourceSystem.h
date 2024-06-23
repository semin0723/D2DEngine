#pragma once
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"
#include "Events.h"
#include "Image.h"
#include "Sprite.h"
#include "wincodec.h"
#pragma comment(lib, "windowscodecs.lib")

class ResourceSystem : public System<ResourceSystem>, public EventListener
{
public:
	ResourceSystem(ID2D1HwndRenderTarget* target);
	~ResourceSystem() {
		for (auto res : _resources) {
			res.second->~Image();
		}
		_wicFactory->Release();
		UnRegistEvent();
	}

	void GetImage(std::wstring spriteKey, Image* image);

	void RegistEvent();
	void UnRegistEvent();

private:
	ID2D1HwndRenderTarget* _target;
	IWICImagingFactory* _wicFactory = { 0 };

	std::unordered_map<std::wstring, Image*> _resources;

	void OnCreateSprite(const CreateSprite* event);
};

