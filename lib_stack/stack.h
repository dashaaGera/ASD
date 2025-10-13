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


#endif