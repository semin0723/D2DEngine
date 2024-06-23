#include "ResourceSystem.h"

ResourceSystem::ResourceSystem(ID2D1HwndRenderTarget* target) : _target(target)
{
	HRESULT res = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_wicFactory)
	);

	RegistEvent();
}

void ResourceSystem::GetImage(std::wstring spriteKey, Image* image)
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

void ResourceSystem::RegistEvent()
{
	RegisterCallback(&ResourceSystem::OnCreateSprite);
}

void ResourceSystem::UnRegistEvent()
{
	UnRegisterCallback(&ResourceSystem::OnCreateSprite);
}

void ResourceSystem::OnCreateSprite(const CreateSprite* event)
{
	if (_resources.find(event->_spriteKey) == _resources.end()) {
		Image* img = new Image;
		GetImage(event->_spriteKey, img);
		_resources.insert({ event->_spriteKey, img });
	}
	ECS::_ecs->GetComponentManager()->AddComponent<Sprite>(event->_entityId, _resources[event->_spriteKey]);
}
