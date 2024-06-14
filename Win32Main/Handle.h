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

	// �ڵ� ���� ��Ʈ�� �ּҰ��� �����մϴ�.
	static constexpr value_type		MIN_VERSION		{ 0 };
	// �ڵ� ���� ��Ʈ�� �ִ밪�� �����մϴ�. 64��Ʈ ���� 0 ~ 2^24 - 2 ��ŭ�� ������ ������, 2^24 - 1�� invalid version���� �����մϴ�.
	static constexpr value_type		MAX_VERSION		{ (1U << NUM_VERSION_BITS) - 2U };
	// �ڵ� �ε��� ��Ʈ�� �ִ밪�� �����մϴ�. 64��Ʈ ���� 0 ~ 2^40 - 2 ��ŭ�� ������ ������, 2^40 - 1�� invalid inedx���� �����մϴ�.
	static constexpr value_type		MAX_INDEX		{ (1U << NUM_INDEX_BITS) - 2U };
	
	// �ڵ��� �ִ밪�� invalid�� �����մϴ�.
	static constexpr value_type		INVALID_HANDLE	{ std::numeric_limits<value_type>::max() };

private:
	value_type	_value;

public:

	// ��������� �ڵ� ���� ����� �⺻ ���� �����ϴ� ���Դϴ�.
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
			
			��. �ڵ��� ������ �ε����� ���� ����� Ŭ������ ������ �� �ִ�.
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

	// �ڵ��� ��ȯ �մϴ�.
	void ReleaseHandle(Handle handle) {
		assert((handle._index < _table.size() && handle._version == _table[handle._index].first) && "Invalid handle");
		_table[handle._index].second = nullptr;
	}

	// �ڵ��� ����ƴ����� ���θ� ������ �Լ�.
	// �ڵ��� ������ �ٸ��� �ش� �ڵ��� �̹� ����� �ڵ��̶� ���� �ڵ��� ��������� �Ұ� ����.
	inline bool IsExpand(Handle handle) const {
		return _table[handle._index].first != handle._version;
	}

	// �ش� �ε����� �ִ� �ڵ��� ��ȯ�մϴ�.
	inline Handle operator[](typename Handle::value_type index) const {
		assert(index < _table.size() && "Invalid handle");
		return Handle(index, _table[index].first);
	}

	// �ڵ��� ����� �ڵ鿡 ���ε� Ŭ������ �����ɴϴ�.
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

	// �ڵ��� �����ϴ� ���̺��� Ȯ���ϴ� �Լ�.
	void ExpandTable() {
		size_t oldSize = _table.size();

		size_t newSize = std::min(oldsize + grow, Handle::MAX_INDEX);

		_table.resize(newSize);
		for (typename Handle::value_type i = oldSize; i < newSize; i++) {
			_table[i] = TableEntry(Handle::MIN_VERSION, nullptr);
		}
	}
};