#include "../lib_itable/itable.h"
#include "../lib_list/list.h"
#include <iostream>
#include <stdexcept>

template <typename TKey, typename TValue>
class UnsortedTableOnList : public ITable<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableOnList() {};
    UnsortedTableOnList(const UnsortedTableOnList&) = delete;
    UnsortedTableOnList& operator=(const UnsortedTableOnList&) = delete;
    ~UnsortedTableOnList()  {};

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    int size() const override;
};

template <typename TKey, typename TValue>
int UnsortedTableOnList<TKey, TValue>::size() const {
    return _rows.size();
}

template <typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == Key) {
            (*it).second = Val;
            return;
        }
    }
    _rows.push_back(std::make_pair(Key, Val));
}

template <typename TKey, typename TValue>
TValue UnsortedTableOnList<TKey, TValue>::find(const TKey& Key) const {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == Key) {
            return (*it).second;
        }
    }
    throw std::logic_error("Key not found");
}

template <typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& Key) {
    int index = 0;
    for (auto it = _rows.begin(); it != _rows.end(); ++it, ++index) {
        if ((*it).first == Key) {
            _rows.erase(index); 
            return;
        }
    }
}

template <typename TKey, typename TValue>
std::ostream& UnsortedTableOnList<TKey, TValue>::print(std::ostream& out) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        out << (*it).first << ": " << (*it).second << std::endl;
    }
    return out;
}

template <typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::consist(const TKey& Key) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == Key) {
            return true;
        }
    }
    return false;
}