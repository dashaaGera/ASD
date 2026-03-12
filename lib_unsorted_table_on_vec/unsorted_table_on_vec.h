#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include <iostream>
template <typename TKey, typename TValue>
class UnsortedTableOnVec :public Table<TKey,TValue, TVector<std::pair<TKey, TValue>>> {
private:
	int find_pos(const TKey& Key) const ;

public:
	UnsortedTableOnVec() {};
	UnsortedTableOnVec(const UnsortedTableOnVec&) = delete;
	UnsortedTableOnVec& operator=(const UnsortedTableOnVec&) = delete;
	~UnsortedTableOnVec() {};
	void insert(const TKey& Key, const TValue& Val) override;
	TValue find(const TKey& Key) const override;
	void erase(const TKey& Key) override;
	//std::ostream& print(std::ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool consist(const TKey& Key) const noexcept override;
	inline int size() const override;

};
template <typename TKey, typename TValue>
inline int UnsortedTableOnVec <typename TKey, typename TValue>::size() const  {
	return _rows.size();
}

template <typename TKey, typename TValue>
int  UnsortedTableOnVec <typename TKey, typename TValue>::find_pos(const TKey& Key) const {
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].first == Key) {
			return i;
		}
		
	}
	return -1;
	
}
template <typename TKey, typename TValue>
void UnsortedTableOnVec <typename TKey, typename TValue>::insert(const TKey& Key, const TValue& Val) {
	int pos = find_pos(Key);
	if(pos!=-1)
		throw std::logic_error("elem exist in the table");
	_rows.push_back(std::make_pair(Key, Val));
}


template <typename TKey, typename TValue>
TValue UnsortedTableOnVec<TKey, TValue>::find(const TKey& Key) const {
	int pos = find_pos(Key);
	if (pos != -1)
		return _rows[pos].second;
	throw std::logic_error("Key not found");
}

template <typename TKey, typename TValue>
void UnsortedTableOnVec <typename TKey, typename TValue>::erase(const TKey& Key)  {
	int pos = find_pos(Key);
		if (pos != -1)
			_rows.erase(pos, 1);		
}



template <typename TKey, typename TValue>
bool UnsortedTableOnVec <typename TKey, typename TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}


template <typename TKey, typename TValue>
bool UnsortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept {
	int pos = find_pos(Key);
		if (pos != -1)
			return true;
	return false;
}