#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdexcept> 
#define MAX_CAPACITY 10000000
#define STEP_CAPACITY 15

template <class T> class TVector;
template <class T> std::ostream& operator<<(std::ostream& out, const TVector<T>& dmass);
template <class T> std::istream& operator>>(std::istream& in, TVector<T>& dmass);

template <class T>
class TVector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;
public:
    TVector();
    TVector(size_t capacity);
    TVector(const TVector& other);
    TVector(T* data, size_t size);
    TVector(std::initializer_list<T> data);
    ~TVector();

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline T* data() const noexcept;

    inline bool is_empty() const;
    inline bool is_full() const;

    void resize(size_t size);
    void reset_memory(size_t new_size);

    void push_back(T val);
    void push_front(T val);
    void insert(size_t pos, T val);

    void pop_back();
    void pop_front();
    void erase(size_t pos, int count = 1);

    inline T front();
    inline T back();
    size_t find_pos(T val);
    T find_val(size_t pos);

    T& operator[](size_t index) ;
    TVector& operator=(const TVector& other);
    const T& operator[](size_t index) const;
    friend std::ostream& operator <<<T>(std::ostream& out, const TVector<T>& dmass);
    friend std::istream& operator >><T>(std::istream& in, TVector<T>& dmass);

    class Iterator {
        T* _ptr;
    public:
        Iterator(T* ptr) : _ptr(ptr) {}

        T& operator*() { return *_ptr; }

        Iterator& operator++() {
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++_ptr;
            return temp;
        }

        Iterator& operator--() {
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --_ptr;
            return temp;
        }

        Iterator& operator -=(int step) {
            _ptr -= step;
            return *this;
        }

        Iterator& operator +=(int step) {
            _ptr += step;
            return *this;
        }
        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return _ptr != other._ptr;
        }
    };

    Iterator begin() { return Iterator(_data); }
    Iterator rbegin() { return Iterator(_data + _size-1); }
    Iterator end() {
        if (_data == nullptr) 
            return Iterator(nullptr);
        else 
            return Iterator(_data + _size);
    }
    Iterator rend() {
        return Iterator(_data-1);
    }
};

template <class T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(0) {}

template <class T>
TVector<T>::TVector(size_t size) : _data(nullptr), _size(size) {
    if (size > MAX_CAPACITY) {
        throw std::invalid_argument("capacity must be less then MAX_CAPACITY");
    }
    _capacity = (size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _data = new T[_capacity];
}

template <class T>
TVector<T>::TVector(const TVector& other) : _data(nullptr), _size(other._size), _capacity(other._capacity) {
    if (this != &other) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
}

template <class T>
TVector<T>::TVector(T* data, size_t size) : _data(nullptr), _size(size) {
    if (size > MAX_CAPACITY) {
        throw std::invalid_argument("size must be less than MAX_CAPACITY");
    }
    _capacity = (size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;

    _data = new T[_capacity];
    for (size_t i = 0; i < size; i++) {
        _data[i] = data[i];
    }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) : _data(nullptr), _size(data.size()) {
    if (data.size() > MAX_CAPACITY) {
        throw std::invalid_argument("size must be less than MAX_CAPACITY");
    }
    _capacity = (_size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = *(data.begin() + i);
    }
}

template <class T>
TVector<T>::~TVector() {
    if (_data != nullptr)
        delete[] _data;
}

template <class T>
inline size_t TVector<T>::size() const  noexcept { return _size; }

template <class T>
inline size_t TVector<T>::capacity() const  noexcept { return _capacity; }

template <class T>
inline T* TVector<T>::data() const  noexcept { return _data; }

template <class T>
inline bool TVector<T>::is_empty() const {
    return _size == 0;
}

template <class T>
inline bool TVector<T>::is_full() const {
    return _capacity > 0 && _size == _capacity;
}

template <class T>
void TVector<T>::resize(size_t size) {
    if (size > MAX_CAPACITY) {
        throw std::logic_error("Size exceeds maximum allowed size");
    }

    if (size > _capacity) {
        size_t new_capacity;

        new_capacity = ((size + STEP_CAPACITY) / STEP_CAPACITY) * STEP_CAPACITY;


        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
    _size = size;
}

template <class T>
void TVector<T>::reset_memory(size_t new_size) {
    size_t new_capacity = (new_size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;

    if (_capacity > new_capacity) {
        T* new_data = new T[new_capacity];

        size_t amount_elem = std::min(_size, new_size);
        for (size_t i = 0; i < amount_elem; i++) {
            new_data[i] = std::move(_data[i]);
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    _size = new_size;
}

template <class T>
void TVector<T>::push_back(T val) {
    if (_capacity == 0 || _size >= _capacity) {
        size_t old_size = _size;
        resize(_size + 1);
        _data[old_size] = val;
    }
    else {
        _data[_size] = val;
        ++_size;
    }
}

template <class T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _size)
        throw std::invalid_argument("reaching out of bounds");
    return _data[index];
}

template <class T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _size)
        throw std::invalid_argument("reaching out of bounds");
    return _data[index];
}


template <class T>
void TVector<T>::push_front(T val) {
    if (_capacity == 0 || _size >= _capacity) {
        size_t old_size = _size;
        resize(_size + 1);
        for (size_t i = old_size; i > 0; --i) {
            _data[i] = _data[i - 1];
        }
        _data[0] = val;
    }
    else {
        for (size_t i = _size; i > 0; --i) {
            _data[i] = _data[i - 1];
        }
        _data[0] = val;
        ++_size;
    }
}

template <class T>
void TVector<T>::insert(size_t pos, T val) {
    if (pos > _size) {
        throw std::out_of_range("Insert position out of range");
    }

    if (_capacity == 0 || _size >= _capacity) {
        size_t old_size = _size;
        resize(_size + 1);
        for (size_t i = old_size; i > pos; --i) {
            _data[i] = _data[i - 1];
        }
        _data[pos] = val;
    }
    else {
        for (size_t i = _size; i > pos; --i) {
            _data[i] = _data[i - 1];
        }
        _data[pos] = val;
        ++_size;
    }
}

template <class T>
void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("Can't pop from empty vector");
    }
    --_size;
    reset_memory(_size);
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::out_of_range("Can't pop from empty vector");
    }

    for (size_t i = 0; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }

    --_size;
    reset_memory(_size);
}

template <class T>
void TVector<T>::erase(size_t pos, int count) {
    if (pos + count > _size || count <= 0) {
        throw std::logic_error("Something went wrong in erase");
    }

    for (size_t i = pos; i < _size - count; i++) {
        _data[i] = _data[i + count];
    }

    _size -= count;
    reset_memory(_size);
}

template <class T>
inline T TVector<T>::front() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[0];
}

template <class T>
inline T TVector<T>::back() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[_size - 1];
}

template <class T>
size_t TVector<T>::find_pos(T val) {
    for (size_t i = 0; i < _size;i++) {
        if (_data[i] == val)
            return i;
    }
    throw std::out_of_range("Value not found in vector");
}


template <class T>
T TVector<T>::find_val(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[pos];
}


template <class T>
std::ostream& operator << <T>(std::ostream& out, const TVector<T>& dmass) {
    for (size_t i = 0; i < dmass.size(); i++) {
        out << dmass[i] << " ";
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, TVector<T>& dmass) {
    size_t size;
    in >> size;
    dmass = TVector<T>(size);
    for (size_t i = 0; i < size; i++) {
        in >> dmass[i];
    }
    return in;
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector& other) {
    if (this != &other) {
        if (_data != nullptr) {
            delete[] _data;
            _data = nullptr;
        }

        _size = other._size;
        _capacity = other._capacity;

        if (other._data != nullptr && _capacity > 0) {
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; i++) {
                _data[i] = other._data[i];
            }
        }
        else {
            _data = nullptr;
        }
    }
    return *this;
}

#endif
