#pragma once
#include "globalheader.h"
#include "Image.h"
#include "Animation.h"
#include "wincodec.h"
#pragma comment(lib, "windowscodecs.lib")
#include <dwrite.h>
#pragma comment(lib,"dwrite.lib")

class ResourceSystem
{
public:
	ResourceSystem() {}
	~ResourceSystem() {
		for (auto& res : _resources) {
			res.second->~Image();
		}
		for (auto& res : _animations) {
			res.second->~Animation();
		}
		_wicFactory->Release();

		for (auto& res : _textformats) {
			res.second->Release();
		}
		_writeFactory->Release();
	}

	static ResourceSystem* GetInstance();
	static void DestroyInstance();

	void Initialize(ID2D1HwndRenderTarget* target);

	void GetImageFromFile(const std::wstring& spriteKey, ID2D1Bitmap** image);
	Image* GetImage(const std::wstring& spriteKey);

	Animation* GetAnimation(const std::wstring& animationKey);
	IDWriteTextFormat* GetTextFormat(std::wstring& fontName, float fontSize);

	void CreateEffectAnimations();

	const std::vector<std::vector<int>>& LoadMapData();

private:
	static ResourceSystem* _instance;

	ID2D1HwndRenderTarget* _target = { 0 };
	IWICImagingFactory* _wicFactory = { 0 };
	IDWriteFactory* _writeFactory = { 0 };

	std::vector<std::vector<int>> _mapdata;

	std::map<std::pair<std::wstring, float>, IDWriteTextFormat*> _textformats;
	std::unordered_map<std::wstring, Image*> _resources;
	std::unordered_map<std::wstring, Animation*> _animations;
};

