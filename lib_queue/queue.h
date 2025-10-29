#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template <class T>
class Queue{
    T* _data;
    int _size;
    int _head;
    int _count;
public:
    Queue(int size = 20);
    Queue(const Queue& other); 
    ~Queue();

    inline T head() const;
    inline int head_index() const noexcept;
    inline T* data() const noexcept;
    inline int size() const noexcept;
    inline int count() const noexcept;

    void push(const T& val);
    void pop();
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template <class T>
Queue<T>::Queue(int size) : _data(new T[size]), _size(size), _head(0), _count(0) {}

template <class T>
Queue<T>::Queue(const Queue& other) :
    _data(new T[other._size]),
    _size(other._size),
    _head(other._head),
    _count(other._count)
{
    for (int i = 0; i < _count; ++i) {
        int index = (other._head + i) % other._size;
        _data[index] = other._data[index];
    }
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template <class T>
inline T Queue<T>::head() const {
    if (is_empty())
        throw std::logic_error("Queue is empty");
    return _data[_head];
}

template <class T>
inline int Queue<T>::head_index() const noexcept {
    return _head;
}

template <class T>
inline T* Queue<T>::data() const noexcept {
    return _data;
}

template <class T>
inline int Queue<T>::size() const noexcept {
    return _size;
}

template <class T>
inline int Queue<T>::count() const noexcept {
    return _count;
}

template <class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count==0;
}

template <class T>
inline bool Queue<T>::is_full() const noexcept {
    return _count==_size;
}

template <class T>
void Queue<T>::push(const T& val) {
    if (is_full())
        throw std::logic_error("Queue is full");
    _count++;
    _data[(_head+_count-1)%_size] = val;
}

template <class T>
void Queue<T>::pop() {
    if (is_empty())
        throw std::logic_error("Queue is empty");
    _count--;
    _head = (++_head) % _size;
}

template <class T>
void Queue<T>::clear() noexcept {
    _head=0;
    _count = 0;
}
#endif