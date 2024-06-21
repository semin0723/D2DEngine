#pragma once
#include "../D2DEngine/D2DRender.h"
#include "ECSCall.h"
#include "utilheader.h"	
#include "EventListener.h"
#include "Events.h"
#include "BoxComponent.h"

struct DrawRectangle : public Event<DrawRectangle> {
	float left;
	float top;
	float right;
	float bottom;
	DrawRectangle(float _left, float _top, float _right, float _bottom) :
		left(_left), top(_top), right(_right), bottom(_bottom)
	{}
};

class RenderSystem : public System<RenderSystem>, public EventListener
{
public:
	RenderSystem(ID2D1HwndRenderTarget* target);
	~RenderSystem();

	virtual void Update(float dt);

private:
	ID2D1HwndRenderTarget* _target;

	void RegistEvent();
	void UnRegistEvent();

	void eventTest(const GameObjectCreated* event);

	struct RenderObject {
		EntityId _eid;
		IEntity* _obj;
		RenderObject(EntityId eid, IEntity* obj) :_eid(eid), _obj(obj) {}
		~RenderObject() {
			_eid = EntityId();
			_obj = nullptr;
		}
	};

	std::vector<RenderObject> _renderObject;
	ID2D1SolidColorBrush* _blackBrush;
};

