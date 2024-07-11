#include "ResourceSystem.h"
#include <fstream>
#include <sstream>

ResourceSystem* ResourceSystem::_instance = nullptr;

ResourceSystem* ResourceSystem::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new ResourceSystem;
	}
	return _instance;
}

void ResourceSystem::DestroyInstance()
{
	if (_instance) delete _instance;
}

void ResourceSystem::Initialize(ID2D1HwndRenderTarget* target)
{
	_target = target;

	HRESULT res = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_wicFactory)
	);
}

Image* ResourceSystem::GetImage(const std::wstring& spriteKey)
{
	if (_resources.find(spriteKey) == _resources.end()) {
		Image* newImage = new Image;
		GetImageFromFile(spriteKey, &newImage->_bitmap);
		_resources.insert({ spriteKey, newImage });
	}
	
	return _resources[spriteKey];
}

Animation* ResourceSystem::GetAnimation(const std::wstring& animationKey)
{
	return _animations[animationKey];
}

void ResourceSystem::CreateEffectAnimations()
{
	std::wstring filename = L"data\\Animation\\EffectAnimationFrame.csv";
	std::wifstream file(filename);
	if (!file.is_open()) return;
	std::wstringstream wss;
	float pixelCount = 0;
	std::wstring line;
	std::wstring tmp;
	std::getline(file, line);
	wss = std::wstringstream(line);
	wss >> pixelCount;

	while (true) {
		
		std::wstring animationKey = L"";
		int frameCount = 0;
		int left = 0;
		int top = 0;
		float timePerFrame = 0;

		std::getline(file, animationKey);
		if (animationKey == L"") break;

		// framecount
		std::getline(file, line);
		wss = std::wstringstream(line);
		wss >> frameCount;

		// frame start idx (left, top)
		std::getline(file, line);
		wss = std::wstringstream(line);
		std::getline(wss, tmp, L',');
		left = _wtoi(tmp.c_str());
		std::getline(wss, tmp, L',');
		top = _wtoi(tmp.c_str());

		// time per frame
		std::getline(file, line);
		timePerFrame = (float)_wtof(line.c_str());

		Animation* newAnimation = new Animation;
		for (int i = 0; i < frameCount; i++) {
			newAnimation->_frames.push_back(FrameInfo(left + i, top, (int)pixelCount, timePerFrame));
		}
		_animations.insert({ animationKey, newAnimation });
	}
}

const std::vector<std::vector<int>>& ResourceSystem::LoadMapData()
{
	if (!_mapdata.empty()) {
		return _mapdata;
	}

	std::wstring filename = L"data\\Map\\MapData.CSV";
	std::wifstream file(filename);
	//if (!file.is_open()) return;

	std::wstringstream wss;
	std::wstring line;
	while (true) {
		std::getline(file, line);
		if (line == L"") break;
		std::vector<int> mapline;

		wss = std::wstringstream(line);
		std::wstring tmp;
		while (std::getline(wss, tmp, L',')) {
			mapline.push_back(_wtoi(tmp.c_str()));
		}
		_mapdata.push_back(mapline);
	}
	return _mapdata;
}

void ResourceSystem::GetImageFromFile(const std::wstring& spriteKey, ID2D1Bitmap** image)
{
	IWICBitmapDecoder* decoder = nullptr;
	IWICFormatConverter* converter = nullptr;
	IWICBitmapFrameDecode* frame = nullptr;

	std::wstring imageFilePath = L"data\\" + spriteKey + L".png";

	HRESULT res = _wicFactory->CreateDecoderFromFilename(
		imageFilePath.c_str(),
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&decoder
	);
	decoder->GetFrame(0, &frame);

	_wicFactory->CreateFormatConverter(&converter);
	converter->Initialize(
		frame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	);

	_target->CreateBitmapFromWicBitmap(converter, nullptr, image);

	if (converter)
		converter->Release();

	if (decoder)
		decoder->Release();

	if (frame)
		frame->Release();
}
