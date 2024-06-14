#pragma once
#include "STL.h"
#include "utilheader.h"

template<
	typename handle_value_type,
	size_t versionBits,
	size_t indexBits
>
union Handle {
	using value_type = handle_value_type;

	static constexpr size_t			NUM_VERSION_BITS	{ versionBits };
	static constexpr size_t			NUM_INDEX_BITS		{ indexBits };

	// 핸들 버전 비트의 최소값을 지정합니다.
	static constexpr value_type		MIN_VERSION		{ 0 };
	// 핸들 버전 비트의 최대값을 지정합니다. 64비트 기준 0 ~ 2^24 - 2 만큼의 범위를 가지고, 2^24 - 1은 invalid version으로 지정합니다.
	static constexpr value_type		MAX_VERSION		{ (1U << NUM_VERSION_BITS) - 2U };
	// 핸들 인덱스 비트의 최대값을 지정합니다. 64비트 기준 0 ~ 2^40 - 2 만큼의 범위를 가지고, 2^40 - 1은 invalid inedx으로 지정합니다.
	static constexpr value_type		MAX_INDEX		{ (1U << NUM_INDEX_BITS) - 2U };
	
	// 핸들의 최대값을 invalid로 지정합니다.
	static constexpr value_type		INVALID_HANDLE	{ std::numeric_limits<value_type>::max() };

private:
	value_type	_value;

public:

	// 여기까지가 핸들 내부 요소의 기본 값을 지정하는 곳입니다.
	struct {
		value_type	_index : NUM_INDEX_BITS;
		value_type	_version : NUM_VERSION_BITS;
	};

	Handle() {}
	Handle(value_type value) : _value(value) {}
	Handle(value_type index, value_type version) : _index(index), _version(version) {}

	inline operator value_type() const { return value; }
};

using Handle64 = Handle<unsigned long long, 24, 40>;

template<class T, class handle_type, size_t grow = 1024>
class HandleTable {
	using Handle = handle_type;

public:
	HandleTable() { ExpandTable(); }
	~HandleTable() {}

	Handle GiveHandle(T* newObject) {
/*
		---- HandleTable ----					    ------ Handle ------
		 < unsigned long long, class >   ->   return ( index,   version )
			Handle version,    class	
			
			즉. 핸들의 버전과 인덱스를 통해 저장된 클래스를 가져올 수 있다.
*/
		typename Handle::value_type i = 0;
		for (; i < _table.size(); i++) {
			if (_table[i].second == nullptr) {
				_table[i].second = newObject;
				if (_table[i].first + 1 > Handle::MAX_VERSION) {
					_table[i].first = Handle::MIN_VERSION;
				}
				else {
					_table[i].first++;
				}
				return Handle(i, _table[i].first);
			}
		}

		ExpandTable();

		_table[i].first = 1;
		_table[i].second = newObject;

		// return Handle( _index, _version )
		return Handle(i, _table[i].first);
	}

	// 핸들을 반환 합니다.
	void ReleaseHandle(Handle handle) {
		assert((handle._index < _table.size() && handle._version == _table[handle._index].first) && "Invalid handle");
		_table[handle._index].second = nullptr;
	}

	// 핸들이 만료됐는지의 여부를 따지는 함수.
	// 핸들의 버전이 다르면 해당 핸들은 이미 만료된 핸들이라 새로 핸들을 연결해줘야 할것 같다.
	inline bool IsExpand(Handle handle) const {
		return _table[handle._index].first != handle._version;
	}

	// 해당 인덱스에 있는 핸들을 반환합니다.
	inline Handle operator[](typename Handle::value_type index) const {
		assert(index < _table.size() && "Invalid handle");
		return Handle(index, _table[index].first);
	}

	// 핸들을 사용해 핸들에 맵핑된 클래스를 가져옵니다.
	inline T* operator[](Handle handle) {
		assert((handle._index < _table.size() && handle._version == _table[handle._index].first) && "Invalid handle");
		if (_table[handle._index].first == handle._version) {
			return _table[handle._index].second;
		}
		else {
			return nullptr;
		}
	}

private:
	using TableEntry = std::pair<typename Handle::value_type, T*>;

	std::vector<TableEntry> _table;

	// 핸들을 보관하는 테이블을 확장하는 함수.
	void ExpandTable() {
		size_t oldSize = _table.size();

		size_t newSize = std::min(oldsize + grow, Handle::MAX_INDEX);

		_table.resize(newSize);
		for (typename Handle::value_type i = oldSize; i < newSize; i++) {
			_table[i] = TableEntry(Handle::MIN_VERSION, nullptr);
		}
	}
};