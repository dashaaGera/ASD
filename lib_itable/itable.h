#include <iostream>
template <typename TKey, typename TValue>
class ITable {
public:
	~ITable() {};
	virtual void insert(const TKey& Key, const TValue& Val) = 0;
	virtual TValue find(const TKey& Key) const = 0;
	virtual void erase(const TKey& Key)  = 0;
	virtual std::ostream& print(std::ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const TKey& Key) const noexcept = 0;
	virtual inline int size() const=0;
};