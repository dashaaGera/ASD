#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <class T>
struct Doubly_Linked_Node 
{
    T value;
    Doubly_Linked_Node<T>* next;
    Doubly_Linked_Node<T>* prev;
    Doubly_Linked_Node(T value_ = T(), Doubly_Linked_Node<T>* next_ = nullptr, Doubly_Linked_Node<T>* prev_ = nullptr);
};

template <class T>
Doubly_Linked_Node<T>::Doubly_Linked_Node(T value_, Doubly_Linked_Node<T>* next_, Doubly_Linked_Node<T>* prev_)
    : value(value_) , next(next_), prev(prev_) {}


template <class T>
class Doubly_Linked_List {
    Doubly_Linked_Node<T>* _head;
    Doubly_Linked_Node<T>* _tail;
    int _count;

public:
    Doubly_Linked_List();
    Doubly_Linked_List(const Doubly_Linked_List& other);
    ~Doubly_Linked_List();

    inline int size() const;
    inline bool is_empty() const;
    inline Doubly_Linked_Node<T>* head() const;
    inline Doubly_Linked_Node<T>* tail() const;

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val);
    void insert(Doubly_Linked_Node<T>* node, const T& val);

    void pop_front();
    void pop_back();
    void erase(int pos);
    void erase(Doubly_Linked_Node<T>* node);

    Doubly_Linked_Node<T>* find(const T& val) const;

    class Iterator {
        Doubly_Linked_Node<T>* current;
    public:
        Iterator() :current(nullptr) {}
        Iterator(Doubly_Linked_Node<T>* pos) :current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }
        T& operator*() {
            return current->value;
        }
        bool operator !=(const Iterator& other)const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            if (current != nullptr) {
                current = current->next;
            }
            return tmp;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Iterator& operator--() {
            if (current != nullptr) {
                current = current->prev;  
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            if (current != nullptr) {     
                current = current->prev;
            }
            return tmp;
        }

    };

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }

};

template <class T>
Doubly_Linked_List<T>::Doubly_Linked_List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
Doubly_Linked_List<T>::Doubly_Linked_List(const Doubly_Linked_List& other) : _head(nullptr), _tail(nullptr), _count(0) {
    _head = new Doubly_Linked_Node<T>(*other._head);
    Doubly_Linked_Node<T>* tmpNode = _head;
    Doubly_Linked_Node<T>* tmpNode1 = other._head->next;
    while (tmpNode1 != nullptr) {
        tmpNode->next = new Doubly_Linked_Node<T>(tmpNode1->value, nullptr, tmpNode);
        tmpNode = tmpNode->next;
        tmpNode1 = tmpNode1->next;
    }
    _tail = tmpNode;
    _count = other.size();
}

template <class T>
Doubly_Linked_List<T>::~Doubly_Linked_List() {
    while (_head != nullptr) {
        Doubly_Linked_Node<T>* temp =_head;
        _head = _head->next;
        delete temp;
    }
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <class T>
inline int Doubly_Linked_List<T>::size() const { 
    return _count; 
}

template <class T>
inline bool Doubly_Linked_List<T>::is_empty() const { 
    return _count == 0; 
}

template <class T>
inline Doubly_Linked_Node<T>* Doubly_Linked_List<T>::head() const {
    return _head; 
}

template <class T>
inline Doubly_Linked_Node<T>* Doubly_Linked_List<T>::tail() const {
    return _tail;
}



template <class T>
void Doubly_Linked_List<T>::push_back(const T& val) noexcept {
    Doubly_Linked_Node<T>* node = new Doubly_Linked_Node<T>(val, nullptr, _tail);
    if (is_empty()) {
        _head = node;
        _tail = node;
        _count++;
        return;
    }
    _tail->next = node;
    _tail = node;
    _count++;
}


template <class T>
void Doubly_Linked_List<T>::push_front(const T& val) noexcept {
    Doubly_Linked_Node<T>* node = new Doubly_Linked_Node<T>(val, _head, nullptr);

    if (!is_empty()) 
        _head->prev = node;  
    else
        _tail = node;      
    _head = node;
    _count++;
}
template <class T>
void Doubly_Linked_List<T>::insert(Doubly_Linked_Node<T>* node, const T& val) {
    if (node == nullptr)
        throw std::logic_error("List is empty");
    Doubly_Linked_Node<T>* new_node = new Doubly_Linked_Node<T>(val, node->next, node);
    node->next = new_node;
    if (new_node->next != nullptr)
        new_node->next->prev = new_node;
    if (_tail == node)
        _tail = new_node;
    _count++;
}

template <class T>
void Doubly_Linked_List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count)
        throw std::logic_error("the position not find on the list");
    if (pos == 0)
        push_front(val);
    else if (pos == _count)
        push_back(val);
    else {
        Doubly_Linked_Node<T>* cur = _head;
        int cur_pos = 0;
        while (cur_pos < pos - 1) {
            cur_pos++;
            cur = cur->next;
        }
        insert(cur, val);
    }
}
template <class T>
void Doubly_Linked_List<T>::pop_front() {
    if (is_empty())
        throw std::logic_error("List is empty");

    Doubly_Linked_Node<T>* temp = _head;
    _head = _head->next;

    if (_head!=nullptr) 
        _head->prev = nullptr;
    else
        _tail = nullptr;

    delete temp;
    _count--;
}

template <class T>
void Doubly_Linked_List<T>::pop_back() {
    if (is_empty())
        throw std::logic_error("List is empty");
    Doubly_Linked_Node<T>* temp = _tail;

    if (_head == _tail) {  
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        _tail = _tail->prev;
        _tail->next = nullptr;
    }

    delete temp;
    _count--;
}

template <class T>
void Doubly_Linked_List<T>::erase(int pos) {
    if (pos < 0 || pos >= _count) 
        throw std::logic_error("Invalid position");

    if (pos == 0) 
        pop_front();
    else if (pos == _count - 1) 
        pop_back();
    else {
        Doubly_Linked_Node<T>* current = _head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        _count--;
    }
}

template <class T>
void Doubly_Linked_List<T>::erase(Doubly_Linked_Node<T>* node) {
    if (node == nullptr) {
        throw std::logic_error("Node is nullptr");
    }

    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else
        _head = node->next;

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else 
        _tail = node->prev;
    delete node;
    _count--;
}

template <class T>
Doubly_Linked_Node<T>* Doubly_Linked_List<T>::find(const T& val) const {
    Doubly_Linked_Node<T>* current = _head;
    while (current != nullptr) {
        if (current->value == val)
            return current;
        current = current->next;
    }
    throw std::logic_error("Value not found in the list");
}


#endif