#pragma once
#include "utilheader.h"

// FamilyTypeId 클래스는 엔티티, 컴포넌트, 시스템에 대한 타입 id를 부여해주는 곳입니다.
// 각 클래스 타입 별로 하위 자식 객체들에게 가족 번호를 부여합니다.

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

