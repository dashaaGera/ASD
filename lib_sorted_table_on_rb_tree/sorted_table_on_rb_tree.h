#include "../lib_itable/itable.h"
#include "../lib_rb_tree/rb_tree.h"
#include <iostream>
#include <stdexcept>
template <typename TKey, typename TValue>
class TableOnRBTree : public Table<TKey, TValue, RBTree<TKey, TValue>> {

public:
    TableOnRBTree() {};
    ~TableOnRBTree() {};

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    int size() const override;
};

template <typename TKey, typename TValue>
bool  TableOnRBTree<TKey, TValue>::consist(const TKey& Key) const noexcept {
    try {
        _rows.find(Key);
        return true;
    }
    catch (const std::logic_error&) {
        return false;
    }
}

template <typename TKey, typename TValue>
void  TableOnRBTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    if (consist(Key))
        throw std::logic_error("elem exist in the table");
    _rows.insert(Key, Val);

}

template <typename TKey, typename TValue>
TValue  TableOnRBTree<TKey, TValue>::find(const TKey& Key) const {
    return _rows.find(Key);
}

template <typename TKey, typename TValue>
void  TableOnRBTree<TKey, TValue>::erase(const TKey& Key) {
    _rows.erase(Key);
}

template <typename TKey, typename TValue>
std::ostream& TableOnRBTree<TKey, TValue>::print(std::ostream& out) const noexcept {
    out << _rows.to_string_sorted();
    return out;
}

template <typename TKey, typename TValue>
bool  TableOnRBTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <typename TKey, typename TValue>
int  TableOnRBTree<TKey, TValue>::size() const {
    return _rows.size();
}
