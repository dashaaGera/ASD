#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include <iostream>

template <typename TKey, typename TValue>
class SortedTableOnVec : public Table<TKey, TValue, TVector<std::pair<TKey, TValue>>> {

public:
    SortedTableOnVec(){};
    ~SortedTableOnVec(){};
    SortedTableOnVec(const SortedTableOnVec&) = delete;
    SortedTableOnVec& operator=(const SortedTableOnVec&) = delete;
    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    //std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    inline int size() const override;

private:
    size_t binary_search(const TKey& Key) const noexcept;
};


template <typename TKey, typename TValue>
size_t SortedTableOnVec<TKey, TValue>::binary_search(const TKey& Key) const noexcept {
    size_t left = 0;
    size_t right = _rows.size(); 

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (_rows[mid].first < Key)
            left = mid + 1;
        else
            right = mid;
    }

    return left; 
}


template <typename TKey, typename TValue>
void SortedTableOnVec<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    size_t pos = binary_search(Key);
    if (pos < _rows.size() && _rows[pos].first == Key) {
        throw std::logic_error("elem exist in the table");
    }
    _rows.insert(pos, std::make_pair(Key, Val));
}


template <typename TKey, typename TValue>
TValue SortedTableOnVec<TKey, TValue>::find(const TKey& Key) const {
    size_t pos = binary_search(Key);

    if (pos < _rows.size() && _rows[pos].first == Key) 
        return _rows[pos].second;
    throw std::logic_error("Key not found");
}


template <typename TKey, typename TValue>
void SortedTableOnVec<TKey, TValue>::erase(const TKey& Key) {
    size_t pos = binary_search(Key);

    if (pos < _rows.size() && _rows[pos].first == Key) {
        _rows.erase(pos, 1); 
    }
}

template <typename TKey, typename TValue>
bool SortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept {
    size_t pos = binary_search(Key);
    return (pos < _rows.size() && _rows[pos].first == Key);
}


template <typename TKey, typename TValue>
bool SortedTableOnVec<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}


template <typename TKey, typename TValue>
inline int SortedTableOnVec<TKey, TValue>::size() const {
    return _rows.size();
}