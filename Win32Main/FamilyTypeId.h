#pragma once
#include "utilheader.h"

// FamilyTypeId Ŭ������ ��ƼƼ, ������Ʈ, �ý��ۿ� ���� Ÿ�� id�� �ο����ִ� ���Դϴ�.
// �� Ŭ���� Ÿ�� ���� ���� �ڽ� ��ü�鿡�� ���� ��ȣ�� �ο��մϴ�.

template<class T>
class FamilyTypeId
{
public:
	template<class F>
	static const TypeId Get() {
		static const TypeId typeId = _count++;
		return typeId;
	}
	static const TypeId Get() { return _count; }

private:
	static TypeId _count;
};

