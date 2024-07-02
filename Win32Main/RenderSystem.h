#pragma once
#include "../D2DEngine/D2DRender.h"
#include "ECSElements.h"
#include "globalheader.h"	
#include "EventListener.h"
#include "World.h"
#include "Events.h"


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
	void SetCurWorld(World* world) { _curWorld = world; }
private:
	ID2D1HwndRenderTarget* _target;
	World* _curWorld = nullptr;

	void RegistEvent();
	void UnRegistEvent();

	void OnObjectCreated(const GameObjectCreated* event);
	void OnObjectDestroyed(const GameObjectDestroyed* event);

	struct RenderObject {
		EntityId _eid;
		IEntity* _obj;
		RenderObject(EntityId eid, IEntity* obj) :_eid(eid), _obj(obj) {}
		~RenderObject() {
			_eid = EntityId();
			_obj = nullptr;
		}
	};

	std::vector<RenderObject> _renderObject[(UINT)Object_Layer::End] = {};
	ID2D1SolidColorBrush* _greenBrush;

	D2D1_MATRIX_3X2_F CalcTransform(Vector3& pos, Vector3& scale, Vector3& rot, Vector3& midPos);
};

