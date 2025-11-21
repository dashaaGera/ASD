#include "../lib_list/list.h"
#ifndef LIB_T_STACK_H_
#define LIB_T_STACK_H_

template <class T>
class Stack {
    List<T> _list;

public:
    Stack();
    Stack(const Stack& other);

    inline T top() const;
    inline int size() const noexcept;
    inline bool is_empty() const noexcept;

    void push(const T& val);
    void pop();
    void clear() noexcept;
};
template <class T>
Stack<T>::Stack() : _list() {}

template <class T>
Stack<T>::Stack(const Stack& other) : _list(other._list) {}

template <class T>
inline T Stack<T>::top() const {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    return _list.tail()->value;
}

template <class T>
inline int Stack<T>::size() const noexcept {
    return _list.size();
}

template <class T>
inline bool Stack<T>::is_empty() const noexcept {
    return _list.is_empty();
}

template <class T>
void Stack<T>::push(const T& val) {
    _list.push_back(val);
}

template <class T>
void Stack<T>::pop() {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    _list.pop_back();
}

template <class T>
void Stack<T>::clear() noexcept {
    while (!is_empty()) {
        pop();
    }
}




#endif