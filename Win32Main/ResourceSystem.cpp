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

	HRESULT hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(_writeFactory),
		reinterpret_cast<IUnknown**>(&_writeFactory));
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

IDWriteTextFormat* ResourceSystem::GetTextFormat(std::wstring& fontName, float fontSize, DWRITE_TEXT_ALIGNMENT textallign, DWRITE_PARAGRAPH_ALIGNMENT paragraphalign)
{
	if (_textformats.find({ fontName, fontSize }) == _textformats.end()) {
		IDWriteTextFormat* textformat = nullptr;

		_writeFactory->CreateTextFormat(
			fontName.c_str(),
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"",
			&textformat
		);

		_textformats[{fontName, fontSize}] = textformat;
	}
	
	_textformats[{fontName, fontSize}]->SetTextAlignment(textallign);
	_textformats[{fontName, fontSize}]->SetParagraphAlignment(paragraphalign);

	return _textformats[{fontName, fontSize}];
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
	file.close();
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
	file.close();
	return _mapdata;
}

const std::vector<Vector3>& ResourceSystem::LoadMonsterWayPoint()
{
	if (!_wayPoint.empty()) {
		return _wayPoint;
	}

	std::wstring filename = L"data\\Map\\MonsterWayPoint.CSV";
	std::wifstream file(filename);
	//if (!file.is_open()) return;
	std::wstringstream wss;
	std::wstring line;
	std::wstring tmp;
	Vector3 offset;
	float tileSize = 0;

	//offset
	std::getline(file, line);
	wss = std::wstringstream(line);
	std::getline(wss, tmp, L',');
	offset.x = (FLOAT)_wtof(tmp.c_str());
	std::getline(wss, tmp, L',');
	offset.y = (FLOAT)_wtof(tmp.c_str());

	// tilesize
	std::getline(file, line);
	wss = std::wstringstream(line);
	wss >> tileSize;

	while (true) {
		std::getline(file, line);
		if (line == L"") break;
		wss = std::wstringstream(line);
		Vector3 pos;
		std::getline(wss, tmp, L',');
		pos.x = _wtoi(tmp.c_str()) * tileSize + offset.x;
		std::getline(wss, tmp, L',');
		pos.y = _wtoi(tmp.c_str()) * tileSize + offset.y;

		_wayPoint.push_back(pos);
	}
	file.close();
	return _wayPoint;
}

void ResourceSystem::LoadTowerData()
{
	std::wstring filename = L"data\\ObjectData\\TowerData.CSV";
	std::wifstream file(filename);

	std::wstringstream wss;
	std::wstring line;

	int tierCount, towerCountPerTier;
	std::getline(file, line);
	wss = std::wstringstream(line);
	wss >> tierCount;

	std::getline(file, line);
	wss = std::wstringstream(line);
	wss >> towerCountPerTier;

	for (int i = 0; i < tierCount; i++) {
		std::vector<TowerInfo> info;
		for (int j = 0; j < towerCountPerTier; j++) {
			TowerInfo towerinfo;
			std::vector<std::wstring> splitResult;
			std::getline(file, line);
			wss = std::wstringstream(line);
			std::wstring tmp;
			while (std::getline(wss, tmp, L',')) {
				splitResult.push_back(tmp);
			}
			towerinfo._towerTier		= (UINT)_wtoi(splitResult[0].c_str());
			towerinfo._towerId			= (UINT)_wtoi(splitResult[1].c_str());
			towerinfo._towerDamage		= _wtoi(splitResult[2].c_str());
			towerinfo._imageDirectory	= splitResult[3];
			towerinfo._detectRange		= (float)_wtof(splitResult[4].c_str());
			towerinfo._attackInterval	= (float)_wtof(splitResult[5].c_str());
			towerinfo._damagePerUpdate	= (UINT)_wtoi(splitResult[6].c_str());
			towerinfo._isAreaAttack		= (bool)_wtoi(splitResult[7].c_str());
			if (towerinfo._isAreaAttack == true) {
				towerinfo._attackArea = Vector3((FLOAT)_wtof(splitResult[8].c_str()), (FLOAT)_wtof(splitResult[9].c_str()), 0);
				towerinfo._effectDirectory = splitResult[10].c_str();
			}
			else {
				towerinfo._attackArea = Vector3();
				towerinfo._effectDirectory = splitResult[8].c_str();
			}
			info.push_back(towerinfo);
		}
		_towerData.push_back(info);
	}
	file.close();
}

const TowerInfo& ResourceSystem::GetTowerInfo(UINT tier, UINT id)
{
	return _towerData[tier - 1][id - 1];
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
