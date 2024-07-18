#include "RenderSystem.h"
#include "Components.h"
#include "Util.h"

RenderSystem::RenderSystem(ID2D1HwndRenderTarget* target) : _target(target)
{
	_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &_greenBrush);
	_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_blackBrush);
	
	RegistEvent();
}

RenderSystem::~RenderSystem()
{
	_greenBrush->Release();
	_blackBrush->Release();
	UnRegistEvent();
}

void RenderSystem::Update(float dt)
{
	D2D1::Matrix3x2F cameraTransform = _curWorld->_mainCamera->GetCameraTransform();
	D2D1InvertMatrix(&cameraTransform);
	D2D1_RECT_F cameraBound = GetBounds(_curWorld->_mainCamera->_cameraPosition, _curWorld->_mainCamera->_cameraSize);

	for (int i = 0; i < (UINT)Object_Layer::UI; i++) {
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
				AnimationComponent* ac = entity._obj->GetComponent<AnimationComponent>();
				if (ac == nullptr) {
					D2D1_RECT_F dest = { 0, 0, (FLOAT)transform->_rectSize.x, (FLOAT)transform->_rectSize.y };
					_target->DrawBitmap(sprite->_sprite->_bitmap, dest);
				}
				else {
					Animation* anim = ac->GetCurAnimation();
					FrameInfo finfo = anim->_frames[ac->_curFrame];
					D2D1_RECT_F dest = { 0, 0, (FLOAT)transform->_rectSize.x, (FLOAT)transform->_rectSize.y };
					D2D1_RECT_F src = { (FLOAT)(finfo._left * finfo._pixelSize), (FLOAT)(finfo._top * finfo._pixelSize),
						(FLOAT)((finfo._left + 1) * finfo._pixelSize),
						(FLOAT)((finfo._top + 1) * finfo._pixelSize) };
					_target->DrawBitmap(sprite->_sprite->_bitmap, dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
				}
					
#ifdef _DEBUG
				_target->DrawRectangle(
					D2D1::RectF(
						bc->_borderPos[0].x, bc->_borderPos[0].y,
						bc->_borderPos[2].x, bc->_borderPos[2].y
					),
					_greenBrush
				);
#endif
			}
		}
	}
	std::sort(_renderObject[(UINT)Object_Layer::UI].begin(), _renderObject[(UINT)Object_Layer::UI].end(), [&](RenderObject& a, RenderObject& b) {
			UIGroup* uileft = ComponentManager->Getcomponent<UIGroup>(a._eid);
			UIGroup* uiright = ComponentManager->Getcomponent<UIGroup>(b._eid);
			return uileft->_groupOrder < uiright->_groupOrder;
		});

	for (int i = _renderObject[(UINT)Object_Layer::UI].size() - 1; i >= 0; i--) {
		if (_renderObject[(UINT)Object_Layer::UI][i]._obj->Active() == false) continue;
		UpdateUI(_renderObject[(UINT)Object_Layer::UI][i]._eid);
	}
	
}

void RenderSystem::UpdateUI(EntityId id)
{
	IEntity* ui = EntityManager->GetEntity(id);
	UITransform* uitf = ui->GetComponent<UITransform>();
	Sprite* sp = ui->GetComponent<Sprite>();
	TextComponent* tc = ComponentManager->Getcomponent<TextComponent>(id);

	_target->SetTransform(uitf->_screenTransform);
	if (tc != nullptr) {
		_target->DrawText(
			tc->_text.c_str(),
			tc->_text.size(),
			ResourceSystem::GetInstance()->GetTextFormat(tc->_font, tc->_fontSize, tc->_textAlignment, tc->_paragraphAlignemt),
			D2D1::RectF(
				0, 0,
				uitf->_size.x, uitf->_size.y
			),
			_blackBrush
		);
	}
	else if (sp == nullptr) {
		_target->FillRectangle(
			D2D1::RectF(
				uitf->_position.x, uitf->_position.y,
				uitf->_position.x + uitf->_size.x,
				uitf->_position.y + uitf->_size.y),
			_greenBrush);
	}
	else {
		_target->DrawBitmap(sp->_sprite->_bitmap, D2D1::RectF(0, 0, uitf->_size.x, uitf->_size.y));
	}

	std::vector<EntityId> child = ui->GetChildEntityId();
	for (auto& i : child) {
		UpdateUI(i);
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
