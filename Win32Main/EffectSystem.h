#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include "EventListener.h"
#include "Events.h"

class EffectSystem : public System<EffectSystem>, public EventListener
{
public:
	EffectSystem();
	~EffectSystem() { UnRegistEvent(); }

	virtual void Update(float dt);

	

	void RegistEvent();
	void UnRegistEvent();

	void OnGameInitialize(const GameInitialize* event);
	void OnCreateEffect(const CreateEffect* event);
	void OnEffectCreated(const GameObjectCreated* event);
	void OnEffectDestroyed(const GameObjectDestroyed* event);
	void OnGamePause(const GamePause* event);

private:
	using Effects = std::vector<EntityId>;

	Effects _effects;

	bool _isGameRunning = true;
};

