#include <iostream>
template <typename TKey, typename TValue>
class ITable {
public:
	~ITable() {};
	virtual void insert(const TKey& Key, const TValue& Val) = 0;
	virtual TValue find(const TKey& Key) const = 0;
	virtual void erase(const TKey& Key)  = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const TKey& Key) const noexcept = 0;
	virtual inline int size() const=0;
};

template <typename TKey, typename TValue, typename TContainer>
class Table:public ITable<TKey, TValue> {
protected:
	TContainer _rows;
public:
	 std::ostream& print(std::ostream& out) const noexcept ;
};

template <typename TKey, typename TValue, typename TContainer>
std::ostream& Table<TKey, TValue, TContainer>::print(std::ostream& out) const noexcept {
	for ( auto it = _rows.begin(); it != _rows.end(); ++it) {
		out << (*it).first << ": " << (*it).second << std::endl;
	}
	return out;
}