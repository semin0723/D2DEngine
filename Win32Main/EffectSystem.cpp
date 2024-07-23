#include "EffectSystem.h"
#include "Components.h"
#include "ResourceSystem.h"
#include "Effect.h"

EffectSystem::EffectSystem()
{
	RegistEvent();
	ResourceSystem::GetInstance()->CreateEffectAnimations();
}

void EffectSystem::Update(float dt)
{
	if (_isGameRunning == false) return;

	AnimationComponent* ac = nullptr; 
	for (int i = 0; i < _effects.size(); i++) {
		AnimationComponent* ac = ComponentManager->Getcomponent<AnimationComponent>(_effects[i]);
		ac->_curTime += dt;
		if (ac->_curTime >= ac->GetCurAnimation()->_frames[ac->_curFrame]._timePerFrame) {
			ac->_curTime -= ac->GetCurAnimation()->_frames[ac->_curFrame]._timePerFrame;
			ac->_curFrame++;
		}

		if (ac->_curFrame == ac->GetCurAnimation()->_frames.size()) {
			if (ac->GetCurAnimation()->_isLoop == false) {
				ecs->SendEvent<GameObjectDestroyed>(_effects[i], Object_Layer::Effect);
				EntityManager->DestroyEntity(_effects[i]);
			}
			else {
				ac->_curFrame %= ac->GetCurAnimation()->_frames.size();
			}
		}
	}
}

void EffectSystem::RegistEvent()
{
	RegisterCallback(&EffectSystem::OnEffectCreated);
	RegisterCallback(&EffectSystem::OnEffectDestroyed);
	RegisterCallback(&EffectSystem::OnCreateEffect);
	RegisterCallback(&EffectSystem::OnGamePause);
	RegisterCallback(&EffectSystem::OnGameInitialize);
}

void EffectSystem::UnRegistEvent()
{
	UnRegisterCallback(&EffectSystem::OnEffectCreated);
	UnRegisterCallback(&EffectSystem::OnEffectDestroyed);
	UnRegisterCallback(&EffectSystem::OnCreateEffect);
	UnRegisterCallback(&EffectSystem::OnGamePause);
	UnRegisterCallback(&EffectSystem::OnGameInitialize);
}

void EffectSystem::OnGameInitialize(const GameInitialize* event)
{
	_effects.clear();
}

void EffectSystem::OnCreateEffect(const CreateEffect* event)
{
	EntityId newEntity = EntityManager->CreateEntity<Effect>();
	Transform* tf = ComponentManager->AddComponent<Transform>(newEntity);
	Sprite* sp = ComponentManager->AddComponent<Sprite>(newEntity, L"Images\\HitEffects");
	BoxCollider* bc = ComponentManager->AddComponent<BoxCollider>(newEntity, Vector3(64.0f, 64.0f, 0));
	AnimationComponent* ac = ComponentManager->AddComponent<AnimationComponent>(newEntity);

	tf->SetRectSize(Vector3(64.0f, 64.0f, 0));
	tf->_position = event->_createLocation - Vector3(14.0f, 14.0f, 0);
	ac->AddAnimation(event->_effectKey, ResourceSystem::GetInstance()->GetAnimation(event->_effectKey));
	ac->_curAnimationState = event->_effectKey;
	ecs->SendEvent<GameObjectCreated>(newEntity, Object_Layer::Effect);
}

void EffectSystem::OnEffectCreated(const GameObjectCreated* event)
{
	if (event->_layer == Object_Layer::Effect || event->_layer == Object_Layer::TileEffect) {
		_effects.push_back(event->_entityId);
	}
}

void EffectSystem::OnEffectDestroyed(const GameObjectDestroyed* event)
{
	for (Effects::iterator it = _effects.begin(); it != _effects.end(); it++) {
		if ((*it) == event->_entityId) {
			_effects.erase(it);
			break;
		}
	}
}

void EffectSystem::OnGamePause(const GamePause* event)
{
	_isGameRunning ^= true;
}
