#pragma once
#include "../D2DEngine/D2DRender.h"
#include "Component.h"
#include "STL.h"

#define BLACK 0
#define GRAY 1

class RenderComponent :
    public Component<RenderComponent>
{
public:
    RenderComponent() : _renderTarget(0), _brushes(10, nullptr) {}
    ~RenderComponent() {}

    void Initialize(ID2D1HwndRenderTarget* _target);
    void Finalize();
    
    void DrawLine(const float _startX, const float _startY, const float _endX, const float _endY, const int _brushType, const float _lineWidth);
    void DrawFillRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
    void DrawRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
    //TODO: ���� ��Ʈ�� �Ǵ� �̹��� ������ �������ϴ� �Լ��� �߰��մϴ�.

private:
    ID2D1HwndRenderTarget* _renderTarget;
    std::vector<ID2D1SolidColorBrush*> _brushes;
};

