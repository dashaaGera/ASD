#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template <class T>
class Stack {
    T* _data;
    int _size;
    int _top;
public:
    Stack(int size = 20);
    Stack(const Stack& other);
    ~Stack();

    inline T top() const;
    inline int top_index() const noexcept;
    inline T* data() const noexcept;
    inline int size() const noexcept;

    void push(const T& val);
    void pop();
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template <class T>
Stack<T>::Stack(int size) : _data(new T[size]), _size(size), _top(-1) {}

template <class T>
Stack<T>::Stack(const Stack& other) :
    _data(new T[other._size]),
    _size(other._size),
    _top(other._top)
{
    for (int i = 0; i <= other._top; ++i) {
        _data[i] = other._data[i];
    }
}

template <class T>
Stack<T>::~Stack() {
    delete[] _data;
}

template <class T>
void Stack<T>::push(const T& val) {
    if (is_full())
        throw std::logic_error("Stack is full");
    _data[++_top] = val;
}

template <class T>
void Stack<T>::pop() {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    --_top;
}

template <class T>
inline T Stack<T>::top() const {
    if (is_empty())
        throw std::logic_error("Stack is empty");
    return _data[_top];
}

template <class T>
inline int Stack<T>::top_index() const noexcept {
    return _top;
}

template <class T>
inline T* Stack<T>::data() const noexcept {
    return _data;
}

template <class T>
inline int Stack<T>::size() const noexcept {
    return _size;
}

template <class T>
inline bool Stack<T>::is_empty() const noexcept {
    return _top == -1;
}

template <class T>
inline bool Stack<T>::is_full() const noexcept {
    return _top == _size - 1;
}

template <class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}

#endif