#include "../lib_list/list.h"
#ifndef LIB_T_STACK_H_
#define LIB_T_STACK_H_

template <class T>
class TStack {
    List<T> _list;

public:
    TStack();
    TStack(const TStack& other);

    inline T top() const;
    inline int size() const noexcept;
    inline bool is_empty() const noexcept;

    void push(const T& val);
    void pop();
    void clear() noexcept;
};
template <class T>
TStack<T>::TStack() : _list() {}

template <class T>
TStack<T>::TStack(const TStack& other) : _list(other._list) {}

template <class T>
inline T TStack<T>::top() const {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    return _list.head()->value;
}

template <class T>
inline int TStack<T>::size() const noexcept {
    return _list.size();
}

template <class T>
inline bool TStack<T>::is_empty() const noexcept {
    return _list.is_empty();
}

template <class T>
void TStack<T>::push(const T& val) {
    _list.push_front(val);
}

template <class T>
void TStack<T>::pop() {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    _list.pop_front();
}

template <class T>
void TStack<T>::clear() noexcept {
    while (!is_empty()) {
        _list.pop_front();
    }
}

#endif