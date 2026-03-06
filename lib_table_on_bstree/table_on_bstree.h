#include "../lib_itable/itable.h"
#include "../lib_bstree/bstree.h"
#include <iostream>
#include <stdexcept>
template <typename TKey, typename TValue>
class TableOnBSTree : public ITable<TKey, TValue> {
    BSTree<TKey, TValue> _tree;

public:
    TableOnBSTree() {};
    ~TableOnBSTree() {};

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    int size() const override;
};

template <typename TKey, typename TValue>
bool TableOnBSTree<TKey, TValue>::consist(const TKey& Key) const noexcept {
    try {
        _tree.find(Key);
        return true;
    }
    catch (const std::logic_error&) {
        return false;
    }
}

template <typename TKey, typename TValue>
void TableOnBSTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    if (consist(Key))
        throw std::logic_error("elem exist in the table");
    _tree.insert(Key, Val);

}

template <typename TKey, typename TValue>
TValue TableOnBSTree<TKey, TValue>::find(const TKey& Key) const {
    return _tree.find(Key);
}

template <typename TKey, typename TValue>
void TableOnBSTree<TKey, TValue>::erase(const TKey& Key) {
    _tree.erase(Key);
}

template <typename TKey, typename TValue>
std::ostream& TableOnBSTree<TKey, TValue>::print(std::ostream& out) const noexcept {
    out<< _tree.to_string_sorted();
    return out;
}

template <typename TKey, typename TValue>
bool TableOnBSTree<TKey, TValue>::is_empty() const noexcept {
    return _tree.is_empty();
}

template <typename TKey, typename TValue>
int TableOnBSTree<TKey, TValue>::size() const {
    return _tree.size();
}
