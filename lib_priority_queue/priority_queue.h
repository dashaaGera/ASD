#include "../lib_heap/heap.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

template <class T>
struct PriorityNode {
    PriorityNode(const T & _name, int _pr, int ord): name(_name), priority(_pr), order(ord) {}
    T name;
    int priority;  // 1 -платно , 2 - по записи, 3 - без записи
    int order;     

    bool operator<(const PriorityNode& other) const;
};

//приоритет 1 -важнее, у кого меньше порядок - важнее
template <class T>
bool PriorityNode<T>::operator<(const PriorityNode& other) const {
    if (priority != other.priority)
        return priority < other.priority;
    return order < other.order;
}

int to_minutes(string time) {
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    return h * 60 + m;
}


template <class T>
class PriorityQueue {
    Heap<PriorityNode<T>> queue;
    int size;
public:
    PriorityQueue() { size = 0; }
    void push(const T& name, int priority);
    T pop();
    bool is_empty();
};


template <class T>
void  PriorityQueue<T>::push(const T& name, int priority ) {
    PriorityNode<T> p = { name,priority,++size };
    queue.insert(p);
}


template <class T>
T PriorityQueue<T>::pop() {
    return queue.erase().name;
}


template <class T>
bool  PriorityQueue<T>::is_empty() {
    return queue.is_empty();
}

