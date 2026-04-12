#pragma once
#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a); 
}

bool is_simple(int a, int b) {
    return gcd(a, b) == 1;
}

template <class TValue>
struct HashData {
    std::string Key;
    TValue val;
    enum State { empty, busy, to_delete };
    State status;

    HashData() : Key(""), val(TValue()), status(empty) {}
    HashData(const std::string& key, const TValue& value) : Key(key), val(value), status(busy) {}
};

template <class TValue>
class HashTableOpenAddress : public ITable<std::string, TValue> {
    TVector<HashData<TValue>> _rows; 
    size_t count;
    size_t _shift;

public:
    HashTableOpenAddress(size_t size = 100);
    ~HashTableOpenAddress() {};

    void insert(const std::string& Key, const TValue& Val) override;
    TValue find(const std::string& Key) const override;
    void erase(const std::string& Key) override;
    std::ostream& print(std::ostream& out) const noexcept;
    bool is_empty() const noexcept override;
    bool is_full() const noexcept;
    bool consist(const std::string& Key) const noexcept override;
    int size() const override;

private:
    size_t h(const std::string& Key) const;
    size_t hh(size_t hash) const;
};

template <class TValue>
size_t HashTableOpenAddress<TValue>::h(const std::string& Key) const {
    size_t hash = 0;
    for (auto sym : Key) {
        hash += sym;
    }
    return hash % _rows.size();
}

template <class TValue>
size_t HashTableOpenAddress<TValue>::hh(size_t hash) const {
    return (hash + _shift) % _rows.size();
}

template <class TValue>
HashTableOpenAddress<TValue>::HashTableOpenAddress(size_t size)
    : _rows(size), count(0), _shift(1)
{
    for (size_t s = 1 + std::max<size_t>(1, _rows.size() / 15); s < _rows.size(); ++s) {
        if (is_simple(static_cast<int>(s), static_cast<int>(size))) {
            _shift = s;
            break;
        }
    }
}

template <class TValue>
bool HashTableOpenAddress<TValue>::is_empty() const noexcept {
    return count == 0;
}

template <class TValue>
bool HashTableOpenAddress<TValue>::is_full() const noexcept {
    return count == _rows.size();
}

template <class TValue>
int HashTableOpenAddress<TValue>::size() const {
    return static_cast<int>(count);
}

template <class TValue>
void HashTableOpenAddress<TValue>::insert(const std::string& Key, const TValue& Val) {
    if (is_full())
        throw std::logic_error("Hash table is full");

    HashData<TValue> new_data(Key, Val); 

    size_t index = h(Key);

    while (true) {
        if (_rows[index].status != HashData<TValue>::busy) {
            _rows[index] = new_data;
            count++;
            return;
        }

        if (_rows[index].Key == Key && _rows[index].status == HashData<TValue>::busy) {
            throw std::logic_error("Key already exists");
        }
        index = hh(index);
    }
}

template <class TValue>
TValue HashTableOpenAddress<TValue>::find(const std::string& Key) const {
    if (is_empty())
        throw std::logic_error("Hash table is empty");

    size_t index = h(Key);
    while (true) {
        if (_rows[index].status == HashData<TValue>::empty) {
            throw std::logic_error("Key not found");
        }

        if (_rows[index].status == HashData<TValue>::busy &&
            _rows[index].Key == Key) {
            return _rows[index].val;
        }

        index = hh(index);
    }

    throw std::logic_error("Key not found");
}

template <class TValue>
bool HashTableOpenAddress<TValue>::consist(const std::string& Key) const noexcept {
    try {
        find(Key);
        return true;
    }
    catch (...) {
        return false;
    }
}


template <class TValue>
void HashTableOpenAddress<TValue>::erase(const std::string& Key) {
    if (is_empty())
        throw std::logic_error("Hash table is empty");

    size_t index = h(Key);

    while (true) {
        if (_rows[index].status == HashData<TValue>::empty) {
            throw std::logic_error("Key not found");
        }

        if (_rows[index].status == HashData<TValue>::busy &&
            _rows[index].Key == Key) {
            _rows[index].status = HashData<TValue>::to_delete;
            count--;
            return;
        }

        index = hh(index);
    }

    throw std::logic_error("Key not found");
}


template <class TValue>
std::ostream& HashTableOpenAddress<TValue>::print(std::ostream& out) const noexcept {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].status == HashData<TValue>::busy) {
            out << "Bucket " << i << ": [" << _rows[i].Key << ": " << _rows[i].val << "]" << std::endl;
        }
    }
    return out;
}