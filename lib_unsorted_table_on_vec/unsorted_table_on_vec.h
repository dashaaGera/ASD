#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include <iostream>
template <typename TKey, typename TValue>
class UnsortedTableOnVec :public ITable<TKey,TValue> {
	TVector<std::pair<TKey, TValue>> _rows;

public:
	UnsortedTableOnVec() {};
	UnsortedTableOnVec(const UnsortedTableOnVec&) = delete;
	UnsortedTableOnVec& operator=(const UnsortedTableOnVec&) = delete;
	~UnsortedTableOnVec() {};
	void insert(const TKey& Key, const TValue& Val) override;
	TValue find(const TKey& Key) const override;
	void erase(const TKey& Key) override;
	std::ostream& print(std::ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool consist(const TKey& Key) const noexcept override;
	inline int size() const override;

};
template <typename TKey, typename TValue>
inline int UnsortedTableOnVec <typename TKey, typename TValue>::size() const  {
	return _rows.size();
}
template <typename TKey, typename TValue>
void UnsortedTableOnVec <typename TKey, typename TValue>::insert(const TKey& Key, const TValue& Val) {
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].first == Key) {
			_rows[i].second = Val;  
			return;
		}
	}
	_rows.push_back(std::make_pair(Key, Val));
}


template <typename TKey, typename TValue>
TValue UnsortedTableOnVec<TKey, TValue>::find(const TKey& Key) const {
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].first == Key) {
			return _rows[i].second;
		}
	}
	throw std::logic_error("Key not found");
}

template <typename TKey, typename TValue>
void UnsortedTableOnVec <typename TKey, typename TValue>::erase(const TKey& Key)  {
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].first == Key) {
			_rows.erase(i, 1);
			return;
		}
	}
}

template <typename TKey, typename TValue>
std::ostream& UnsortedTableOnVec<TKey, TValue>::print(std::ostream& out) const noexcept {
	for (size_t i = 0; i < _rows.size(); ++i) {
		out << _rows[i].first << ": " << _rows[i].second << std::endl;
	}
	return out;
}

template <typename TKey, typename TValue>
bool UnsortedTableOnVec <typename TKey, typename TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}


template <typename TKey, typename TValue>
bool UnsortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept {
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].first == Key) {
			return true;
		}
	}
	return false;
}