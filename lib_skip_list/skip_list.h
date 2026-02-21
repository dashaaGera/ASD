#include "../lib_list/list.h"
#include <iostream>
#include <limits>
template <typename TKey, typename TValue>
struct SkipNode {
    std::pair<TKey, TValue> data;
    size_t levels;
    SkipNode** next;
    SkipNode(const TKey& key, const TValue& value, size_t lvl);
    ~SkipNode();
};

template <typename TKey, typename TValue>
SkipNode<TKey, TValue>::SkipNode(const TKey& key, const TValue& value, size_t lvl): data(key, value), levels(lvl) {
    next = new SkipNode * [lvl + 1];
    for (size_t i = 0; i <= lvl; i++)
        next[i] = nullptr;
}

template <typename TKey, typename TValue>
SkipNode<TKey, TValue>::~SkipNode() {
    delete[] next;
}

template <typename TKey, typename TValue>
class SkipList {
private:
    List<SkipNode<TKey, TValue>*> heads;  
    size_t current_level;
    size_t max_level;

    size_t generate_level() {
        size_t level = 0; 
        while (level < max_level && rand() % 100 < 50)
            level++;
        return level;
    }

public:
    SkipList(size_t max_lvl = 16);
    ~SkipList();
    SkipNode<TKey, TValue>* find(const TKey& key);
    void insert(const TKey& key, const TValue& value);
    bool is_empty() const { return heads.is_empty() || heads.head()->value->next[0] == nullptr; };
}; 

template <typename TKey, typename TValue>
SkipList<TKey, TValue>::SkipList(size_t max_lvl ) : current_level(0), max_level(max_lvl) {
    std::srand(std::time(nullptr));
    for (size_t i = 0; i <= max_level; i++) {
        SkipNode<TKey, TValue>* head_node = new SkipNode<TKey, TValue>(std::numeric_limits<TKey>::min(),TValue(), max_level);
        heads.push_back(head_node);
    }
}

template <typename TKey, typename TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (!heads.is_empty()) {
        SkipNode<TKey, TValue>* current = heads.head()->value->next[0];
        //delete all skip_nodes on first level
        while (current != nullptr) {
            SkipNode<TKey, TValue>* temp = current;
            current = current->next[0];
            delete temp;
        }

        //delete 'fictitious' list
        for (auto it = heads.begin(); it != heads.end(); ++it) {
            delete* it;
        }
    }
}

template <typename TKey, typename TValue>
SkipNode<TKey, TValue>* SkipList<TKey, TValue>::find(const TKey& key) {
    SkipNode<TKey, TValue>* current = heads.head()->value;
    for (int i = current_level; i >= 0; --i) {
        // forward when next elem < key
        while (current->next[i] != nullptr &&
            current->next[i]->data.first < key) {
            current = current->next[i]; 
        }
        // get down,when elem>key
    } 
    current = current->next[0];
    if (current != nullptr && current->data.first == key)
        return current;
    return nullptr;  
}


template <typename TKey, typename TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    SkipNode<TKey, TValue>** prev_at_level = new SkipNode<TKey, TValue>* [max_level + 1];

    //find
    SkipNode<TKey, TValue>* current = heads.head()->value;
    for (int level = current_level; level >= 0; level--) {
        while (current->next[level] &&
            current->next[level]->data.first < key) {
            current = current->next[level];
        }
        // pos, when stop
        prev_at_level[level] = current;
    }

    current = current->next[0];
    if (current && current->data.first == key) {
        current->data.second = value;
        delete[] prev_at_level;
        return;
    }

    size_t new_height = generate_level();

    // if insert_node height > curr, update "prev" for new levels
    if (new_height > current_level) {
        for (size_t level = current_level + 1; level <= new_height; level++) {
            prev_at_level[level] = heads.head()->value; //insert after head
        }
        current_level = new_height;
    }

    SkipNode<TKey, TValue>* insert_node = new SkipNode<TKey, TValue>(key, value, new_height);

    // insert
    for (size_t level = 0; level <= new_height; level++) {
        insert_node->next[level] = prev_at_level[level]->next[level];
        prev_at_level[level]->next[level] = insert_node;
    }

    delete[] prev_at_level;
}

