#pragma once
#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include <iostream>
#include <stdexcept>
#include <string>
template <class TValue>
class HashTableChain : public ITable<std::string,TValue> {
    TVector<List<std::pair<std::string, TValue>>> _rows;
    size_t count;

public:
    HashTableChain(size_t size=100):_rows(size),count(0) {};
    ~HashTableChain() {};

    void insert(const std::string& Key, const TValue& Val) override;
    TValue find(const std::string& Key) const override;
    void erase(const std::string& Key) override;
    std::ostream& print(std::ostream& out) const noexcept;
    bool is_empty() const noexcept override;
    bool consist(const std::string& Key) const noexcept override;
    int size() const override;

private:
    size_t h(const std::string &Key) const;
};

template <class TValue>
size_t HashTableChain<TValue>::h(const std::string& Key) const {
    size_t hash = 0; 
    for (auto sym : Key) {
        hash += sym;
    }
    return hash % _rows.size(); 
}

template <class TValue>
void HashTableChain<TValue>::insert(const std::string& Key, const TValue& Val) {
    std::pair<std::string, TValue> new_data = { Key, Val };  
    size_t index = h(Key); 

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == Key) {
            throw std::logic_error("Key already exists");
        }
    }
    _rows[index].push_back(new_data);
    count++;
}

template <class TValue>
TValue HashTableChain<TValue>::find(const std::string& Key) const {  
    size_t index = h(Key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == Key) {
            return (*it).second;
        }
    }
    throw std::logic_error("Key not found");
}

template <class TValue>
void HashTableChain<TValue>::erase(const std::string& Key) {
    size_t index = h(Key); 
    size_t pos = 0;
    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == Key) {
            _rows[index].erase(pos);
            count--;
            return;
        }
        pos++;
    }
    throw std::logic_error("Key not found");
}

template <class TValue>
std::ostream& HashTableChain<TValue>::print(std::ostream& out) const noexcept {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (!_rows[i].is_empty()) { 
            out << "Bucket " << i << ": ";
            for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
                out << "[" << (*it).first << ": " << (*it).second << "] ";
            }
            out << std::endl;
        }
    }
    return out;
}

template <class TValue>
bool HashTableChain<TValue>::consist(const std::string& Key) const noexcept {
    try {
        find(Key);
        return true;
    }
    catch (...) {
        return false;
    }
}

template <class TValue>
bool HashTableChain<TValue>::is_empty() const noexcept {
    return count == 0; 
}

template <class TValue>
int HashTableChain<TValue>::size() const {
    return static_cast<int>(count);
}

template <class TValue>
HashTableChain< TValue> merge_dict(TVector<std::pair<std::string, TValue>> dict1, TVector<std::pair<std::string, TValue>> dict2) {
    HashTableChain<TValue> result;

    for (auto it = dict1.begin(); it != dict1.end(); ++it) {
        result.insert((*it).first, (*it).second);
    }

    for (auto it = dict2.begin(); it != dict2.end(); ++it) {
        if (!result.consist((*it).first)) {
            result.insert((*it).first, (*it).second);
        }
    }

    return result;
}