#include "RenderComponent.h"

void RenderComponent::Initialize(ID2D1HwndRenderTarget* _target)
{
	_renderTarget = _target;

	_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_brushes[0]);
	_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &_brushes[1]);
}

void RenderComponent::Finalize()
{
	for (int i = 0; i < _brushes.size(); i++) {
		if (_brushes[i] != nullptr) _brushes[i]->Release();
	}
}

void RenderComponent::DrawLine(const float _startX, const float _startY, const float _endX, const float _endY, const int _brushType, const float _lineWidth)
{
	_renderTarget->DrawLine(
		D2D1::Point2F(_startX, _startY),
		D2D1::Point2F(_endX, _endY),
		_brushes[_brushType], _lineWidth
	);
}

void RenderComponent::DrawFillRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType)
{
	_renderTarget->FillRectangle(
		D2D1::RectF(
			_left, _top,
			_right, _bottom
		), 
		_brushes[_brushType]
	);
}

void RenderComponent::DrawRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType)
{
	_renderTarget->DrawRectangle(
		D2D1::RectF(
			_left, _top,
			_right, _bottom
		), 
		_brushes[_brushType]
	);
}
