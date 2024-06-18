#pragma once
#include "EventDelegate.h"
#include "EventHandler.h"
#include "utilheader.h"

class EventListener
{
	using RegisteredCallbacks = std::list<IEventDelegate*>;
	RegisteredCallbacks _callbacks;

public:
	EventListener();
	virtual ~EventListener();

	template<class E, class C>
	void RegisterCallback(void(C::* Callback)(const E* const)) {
		IEventDelegate* newDelegate = new EventDelegate<C, E>(static_cast<C*>(this), Callback);

		_callbacks.push_back(newDelegate);
		// 임시로 이벤트 리스너가 모든 이벤트를 관리하는 개체로 전환. 또는 DemoApp이 모든 파일들을 가지고 있게 임시로 설정.
		// engine->SubscribeEvent<E>(newDelegate);
		_eventHandler->AddEventCallback(newDelegate);
	}

private:
	EventHandler* _eventHandler;
};

