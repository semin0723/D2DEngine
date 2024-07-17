#pragma once
#include "globalheader.h"
#include "Image.h"
#include "Animation.h"
#include "wincodec.h"
#pragma comment(lib, "windowscodecs.lib")
#include <dwrite.h>
#pragma comment(lib,"dwrite.lib")

struct TowerInfo {
	UINT _towerTier;
	UINT _towerId;
	int _towerDamage;
	std::wstring _imageDirectory;
	float _detectRange;
	float _attackInterval;
	UINT _damagePerUpdate;
	bool _isAreaAttack;
	Vector3 _attackArea;
	std::wstring _effectDirectory;
};

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
	IDWriteTextFormat* GetTextFormat(std::wstring& fontName, float fontSize, DWRITE_TEXT_ALIGNMENT textallign, DWRITE_PARAGRAPH_ALIGNMENT paragraphalign);

	void CreateEffectAnimations();

	const std::vector<std::vector<int>>& LoadMapData();
	const std::vector<Vector3>& LoadMonsterWayPoint();
	void LoadTowerData();

	const TowerInfo& GetTowerInfo(UINT tier, UINT id);

private:
	static ResourceSystem* _instance;

	ID2D1HwndRenderTarget* _target = { 0 };
	IWICImagingFactory* _wicFactory = { 0 };
	IDWriteFactory* _writeFactory = { 0 };

	std::vector<std::vector<int>> _mapdata;
	std::vector<Vector3> _wayPoint;

	std::vector<std::vector<TowerInfo>> _towerData;

	std::map<std::pair<std::wstring, float>, IDWriteTextFormat*> _textformats;
	std::unordered_map<std::wstring, Image*> _resources;
	std::unordered_map<std::wstring, Animation*> _animations;
};

