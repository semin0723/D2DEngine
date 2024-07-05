#include "RenderSystem.h"
#include "Components.h"
#include "Util.h"

RenderSystem::RenderSystem(ID2D1HwndRenderTarget* target) : _target(target)
{
	_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &_greenBrush);
	RegistEvent();
}

RenderSystem::~RenderSystem()
{
	_greenBrush->Release();
	UnRegistEvent();
}

void RenderSystem::Update(float dt)
{
	D2D1::Matrix3x2F cameraTransform = _curWorld->_mainCamera->GetCameraTransform();
	D2D1InvertMatrix(&cameraTransform);
	D2D1_RECT_F cameraBound = GetBounds(_curWorld->_mainCamera->_cameraPosition, _curWorld->_mainCamera->_cameraSize);

	for (int i = 0; i < (UINT)Object_Layer::End; i++) {
		for (auto& entity : _renderObject[i]) {
			Transform* transform = entity._obj->GetComponent<Transform>();
			Sprite* sprite = entity._obj->GetComponent<Sprite>();
			if (transform == nullptr || sprite == nullptr) continue;

			BoxCollider* bc = entity._obj->GetComponent<BoxCollider>();
			if (bc == nullptr) continue;

			D2D1_RECT_F objBound = bc->_bounds;
			if (CheckBorder(cameraBound, objBound) == true) {
				_target->SetTransform(transform->GetTransform() * cameraTransform);
				// 몬스터 40px, 포탑 96px, 이펙트 64px
				if(i == (UINT)Object_Layer::Monster) _target->DrawBitmap(sprite->_sprite->_bitmap, D2D1::RectF(0, 0, 40, 40));
				else {
					AnimationComponent* ac = entity._obj->GetComponent<AnimationComponent>();
					if (ac == nullptr) {
						_target->DrawBitmap(sprite->_sprite->_bitmap);
					}
					else {
						Animation* anim = ac->GetCurAnimation();
						FrameInfo finfo = anim->_frames[ac->_curFrame];
						D2D1_RECT_F dest = { 0, 0, finfo._pixelSize, finfo._pixelSize };
						D2D1_RECT_F src = { finfo._left * finfo._pixelSize, finfo._top * finfo._pixelSize, 
							(finfo._left + 1) * finfo._pixelSize, 
							(finfo._top + 1) * finfo._pixelSize };
						_target->DrawBitmap(sprite->_sprite->_bitmap, dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
					}
					
				}
				_target->DrawRectangle(
					D2D1::RectF(
						bc->_borderPos[0].x, bc->_borderPos[0].y,
						bc->_borderPos[2].x, bc->_borderPos[2].y
					),
					_greenBrush
				);
			}
		}
	}
}

void RenderSystem::RegistEvent()
{
	RegisterCallback(&RenderSystem::OnObjectCreated);
	RegisterCallback(&RenderSystem::OnObjectDestroyed);
}

void RenderSystem::UnRegistEvent()
{
	UnRegisterCallback(&RenderSystem::OnObjectCreated);
	UnRegisterCallback(&RenderSystem::OnObjectDestroyed);
}

void RenderSystem::OnObjectCreated(const GameObjectCreated* event)
{
	IEntity* entity = EntityManager->GetEntity(event->_entityId);
	_renderObject[(UINT)event->_layer].push_back(RenderObject(event->_entityId, entity));
}

void RenderSystem::OnObjectDestroyed(const GameObjectDestroyed* event)
{
	for (auto it = _renderObject[(UINT)event->_layer].begin(); it != _renderObject[(UINT)event->_layer].end(); it++) {
		if ((*it)._eid == event->_entityId) {
			_renderObject[(UINT)event->_layer].erase(it);
			break;
		}
	}
}

D2D1_MATRIX_3X2_F RenderSystem::CalcTransform(Vector3& pos, Vector3& scale, Vector3& rot, Vector3& spriteMid)
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Rotation(rot.z, D2D1::Point2F(spriteMid.x, spriteMid.y)) *
		D2D1::Matrix3x2F::Translation(pos.x, pos.y)
		;
}
