#include "../lib_itable/itable.h"
#include "../lib_list/list.h"
#include <iostream>
#include <stdexcept>

template <typename TKey, typename TValue>
class UnsortedTableOnList : public Table<TKey, TValue, List<std::pair<TKey, TValue>>> {
private:
    Node<std::pair<TKey, TValue>>* find_node(const TKey& Key) const;

public:
    UnsortedTableOnList() {};
    UnsortedTableOnList(const UnsortedTableOnList&) = delete;
    UnsortedTableOnList& operator=(const UnsortedTableOnList&) = delete;
    ~UnsortedTableOnList()  {};

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    //std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    int size() const override;
};

template <typename TKey, typename TValue>
int UnsortedTableOnList<TKey, TValue>::size() const {
    return _rows.size();
}


template <typename TKey, typename TValue>
Node<std::pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_node(const TKey& Key) const
{
    Node<std::pair<TKey, TValue>>* cur = _rows.head(); 
    while (cur != nullptr) {
        if (cur->value.first == Key)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}


template <typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& Key, const TValue& Val)
{
    if (find_node(Key) != nullptr)
        throw std::logic_error("elem exist in the table");
    _rows.push_back(std::make_pair(Key, Val));
}

template <typename TKey, typename TValue>
TValue UnsortedTableOnList<TKey, TValue>::find(const TKey& Key) const{
    Node<std::pair<TKey, TValue>>* node = find_node(Key);
    if (!node)
        throw std::logic_error("Key not found");

    return node->value.second;
}

template <typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& Key)
{
    Node<std::pair<TKey, TValue>>* node = find_node(Key);
    if (node)
        _rows.erase(node); 
}

template <typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::consist(const TKey& Key) const noexcept
{
    return find_node(Key) != nullptr;
}



template <typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

