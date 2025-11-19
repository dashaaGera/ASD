#include "../lib_list/list.h"
#ifndef LIB_T_QUEUE_H_
#define LIB_T_QUEUE_H_

template <class T>
class Queue {
    List<T> _list;

public:
    Queue();
    Queue(const Queue& other);

    inline T head() const;
    inline int size() const noexcept;

    void push(const T& val);
    void pop();
    inline bool is_empty() const noexcept;
    void clear() noexcept;

};

template <class T>
Queue<T>::Queue() : _list() {}

template <class T>
Queue<T>::Queue(const Queue& other) : _list(other._list) {}

template <class T>
inline T Queue<T>::head() const {
    if (is_empty())
        throw std::logic_error("Queue is empty");
    return _list.head()->value;
}

template <class T>
inline int Queue<T>::size() const noexcept {
    return _list.size();  
}

template <class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _list.is_empty();
}


template <class T>
void Queue<T>::push(const T& val) {
    _list.push_back(val);  
}

template <class T>
void Queue<T>::pop() {
    if (is_empty())
        throw std::logic_error("Queue is empty");
    _list.pop_front();  
}

template <class T>
void Queue<T>::clear() noexcept {
    while (!is_empty()) {
        pop();
    }
}

#endif