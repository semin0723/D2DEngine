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

Image* ResourceSystem::GetImage(std::wstring& spriteKey)
{
	if (_resources.find(spriteKey) == _resources.end()) {
		Image* newImage = new Image;
		GetImageFromFile(spriteKey, &newImage->_bitmap);
		_resources.insert({ spriteKey, newImage });
	}
	
	return _resources[spriteKey];
}

Animation* ResourceSystem::GetAnimation(std::wstring& animationKey)
{
	if (_animations.find(animationKey) == _animations.end()) {
		Animation* animation = new Animation;
		GetFrameInfoFromFile(animationKey, animation);
		_animations.insert({ animationKey, animation });
	}

	return _animations[animationKey];
}

void ResourceSystem::GetFrameInfoFromFile(std::wstring& animationKey, Animation* animation)
{
	std::wstring filename = L"data\\Animation\\FrameInfo\\" + animationKey + L".CSV";
	std::wifstream file(filename);
	if (!file.is_open()) {
		return;
	}
	std::wstring line;

	int frameCount = 0;
	std::getline(file, line);
	std::wstringstream wss(line);
	wss >> frameCount;

	for (int i = 0; i < frameCount; i++) {
		FrameInfo frame;
		getline(file, line);
		std::wstringstream wss(line);
		std::wstring tmp;
		std::getline(wss, tmp, L',');
		frame._left = (float)_wtoi(tmp.c_str());
		std::getline(wss, tmp, L',');
		frame._top = (float)_wtoi(tmp.c_str());
		std::getline(wss, tmp, L',');
		frame._right = (float)_wtoi(tmp.c_str());
		std::getline(wss, tmp, L',');
		frame._bottom = (float)_wtoi(tmp.c_str());
		std::getline(wss, tmp, L',');
		frame._playTime = (float)_wtoi(tmp.c_str());
		animation->_frames.push_back(frame);
	}
}

void ResourceSystem::GetImageFromFile(std::wstring& spriteKey, ID2D1Bitmap** image)
{
	IWICBitmapDecoder* decoder = nullptr;
	IWICFormatConverter* converter = nullptr;
	IWICBitmapFrameDecode* frame = nullptr;

	std::wstring imageFilePath = L"data\\Images\\" + spriteKey + L".png";

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
