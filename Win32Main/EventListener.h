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
		// �ӽ÷� �̺�Ʈ �����ʰ� ��� �̺�Ʈ�� �����ϴ� ��ü�� ��ȯ. �Ǵ� DemoApp�� ��� ���ϵ��� ������ �ְ� �ӽ÷� ����.
		// engine->SubscribeEvent<E>(newDelegate);
		_eventHandler->AddEventCallback(newDelegate);
	}

private:
	EventHandler* _eventHandler;
};

