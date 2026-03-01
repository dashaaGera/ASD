#include "../lib_itable/itable.h"
#include "../lib_binary_tree/binary_tree.h"
#include <iostream>
#include <stdexcept>
template <typename TKey, typename TValue>
class UnsortedTableOnBinaryTree : public ITable<TKey, TValue> {
    Tree<TKey, TValue> _tree;

public:
    UnsortedTableOnBinaryTree() {};
    ~UnsortedTableOnBinaryTree() {};

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    int size() const override;
};

template <typename TKey, typename TValue>
bool UnsortedTableOnBinaryTree<TKey, TValue>::consist(const TKey& Key) const noexcept {
    try {
        _tree.find(Key);
        return true;
    }
    catch (const std::logic_error&) {
        return false;
    }
}

template <typename TKey, typename TValue>
void UnsortedTableOnBinaryTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    if(consist(Key))
        _tree.erase(Key);
     _tree.insert(Key, Val);
    
}

template <typename TKey, typename TValue>
TValue UnsortedTableOnBinaryTree<TKey, TValue>::find(const TKey& Key) const {
    return _tree.find(Key);
}

template <typename TKey, typename TValue>
void UnsortedTableOnBinaryTree<TKey, TValue>::erase(const TKey& Key) {
    _tree.erase(Key);
}

template <typename TKey, typename TValue>
std::ostream& UnsortedTableOnBinaryTree<TKey, TValue>::print(std::ostream& out) const noexcept {
    _tree.print_width();  
    return out;
}

template <typename TKey, typename TValue>
bool UnsortedTableOnBinaryTree<TKey, TValue>::is_empty() const noexcept {
    return _tree.is_empty();
}

template <typename TKey, typename TValue>
int UnsortedTableOnBinaryTree<TKey, TValue>::size() const {
    return _tree.size();
}
