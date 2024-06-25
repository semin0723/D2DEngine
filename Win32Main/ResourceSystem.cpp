#include "ResourceSystem.h"

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
		GetImageFromFile(spriteKey, newImage);
		_resources.insert({ spriteKey, newImage });
	}
	
	return _resources[spriteKey];
}

void ResourceSystem::GetImageFromFile(std::wstring& spriteKey, Image* image)
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

	_target->CreateBitmapFromWicBitmap(converter, nullptr, &image->_bitmap);

	if (converter)
		converter->Release();

	if (decoder)
		decoder->Release();

	if (frame)
		frame->Release();
}
