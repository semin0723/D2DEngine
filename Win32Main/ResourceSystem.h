#pragma once
#include "globalheader.h"
#include "Image.h"
#include "wincodec.h"
#pragma comment(lib, "windowscodecs.lib")

class ResourceSystem
{
public:
	ResourceSystem() {}
	~ResourceSystem() {
		for (auto res : _resources) {
			res.second->~Image();
		}
		_wicFactory->Release();
	}

	static ResourceSystem* GetInstance();
	static void DestroyInstance();

	void Initialize(ID2D1HwndRenderTarget* target);
	void GetImageFromFile(std::wstring& spriteKey, Image* image);
	Image* GetImage(std::wstring& spriteKey);

private:
	static ResourceSystem* _instance;

	ID2D1HwndRenderTarget* _target = { 0 };
	IWICImagingFactory* _wicFactory = { 0 };

	std::unordered_map<std::wstring, Image*> _resources;
};

