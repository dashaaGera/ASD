#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "../lib_list/list.h"

template <class T>
class Doubly_Linked_List : public List<T> {
public:
    Doubly_Linked_List();
    Doubly_Linked_List(const Doubly_Linked_List& other);
    ~Doubly_Linked_List() = default;

    virtual void push_front(const T& val) noexcept override;
    virtual void push_back(const T& val) noexcept override;
    virtual void insert(int pos, const T& val) override;
    virtual void insert(Node<T>* node, const T& val) override;
    virtual void pop_front() override;
    virtual void pop_back() override;
    virtual void erase(int pos) override;
    virtual void erase(Node<T>* node) override;
    
    class Iterator : public List<T>::Iterator {
    public:
        Iterator() : List<T>::Iterator() {}
        Iterator(Node<T>* pos) : List<T>::Iterator(pos) {}
        Iterator(const Iterator& other) : List<T>::Iterator(other) {}

        Iterator& operator--() {
            if (this->current != nullptr) {
                this->current = this->current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            if (this->current != nullptr) {
                this->current = this->current->prev;
            }
            return tmp;
        }
    };
    Iterator begin() const  { return Iterator(this->_head); }
    Iterator end() const { return Iterator(nullptr); }
    Iterator rbegin() const { return Iterator(this->_tail); }
    Iterator rend() const { return Iterator(nullptr); }
};

template <class T>
Doubly_Linked_List<T>::Doubly_Linked_List() : List<T>() {}

template <class T>
Doubly_Linked_List<T>::Doubly_Linked_List(const Doubly_Linked_List& other) : List<T>(other) {
    if (!this->is_empty()) {
        Node<T>* current = this->_head;
        Node<T>* prev = nullptr;
        while (current != nullptr) {
            current->prev = prev;
            prev = current;
            current = current->next;
        }
    }
}

template <class T>
void Doubly_Linked_List<T>::push_back(const T& val) noexcept {
    Node<T>* node = new Node<T>(val, nullptr, this->_tail);
    if (this->is_empty()) {
        this->_head = node;
        this->_tail = node;
        this->_count++;
        return;
    }
    this->_tail->next = node;
    this->_tail = node;
    this->_count++;
}

template <class T>
void Doubly_Linked_List<T>::push_front(const T& val) noexcept {
    Node<T>* node = new Node<T>(val, this->_head, nullptr);

    if (!this->is_empty())
        this->_head->prev = node;
    else
        this->_tail = node;
    this->_head = node;
    this->_count++;
}

template <class T>
void Doubly_Linked_List<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr)
        throw std::logic_error("List is empty");
    Node<T>* new_node = new Node<T>(val, node->next, node);
    node->next = new_node;
    if (new_node->next != nullptr)
        new_node->next->prev = new_node;
    if (this->_tail == node)
        this->_tail = new_node;
    this->_count++;
}

template <class T>
void Doubly_Linked_List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > this->_count)
        throw std::logic_error("the position not find on the list");
    if (pos == 0)
        push_front(val);
    else if (pos == this->_count)
        push_back(val);
    else {
        Node<T>* cur = this->_head;
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
    if (this->is_empty())
        throw std::logic_error("List is empty");

    Node<T>* temp = this->_head;
    this->_head = this->_head->next;

    if (this->_head != nullptr)
        this->_head->prev = nullptr;
    else
        this->_tail = nullptr;

    delete temp;
    this->_count--;
}

template <class T>
void Doubly_Linked_List<T>::pop_back() {
    if (this->is_empty())
        throw std::logic_error("List is empty");
    Node<T>* temp = this->_tail;

    if (this->_head == this->_tail) {
        this->_head = nullptr;
        this->_tail = nullptr;
    }
    else {
        this->_tail = this->_tail->prev;
        this->_tail->next = nullptr;
    }

    delete temp;
    this->_count--;
}

template <class T>
void Doubly_Linked_List<T>::erase(int pos) {
    if (pos < 0 || pos >= this->_count)
        throw std::logic_error("Invalid position");

    if (pos == 0)
        pop_front();
    else if (pos == this->_count - 1)
        pop_back();
    else {
        Node<T>* current = this->_head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        this->_count--;
    }
}

template <class T>
void Doubly_Linked_List<T>::erase(Node<T>* node) {
    if (node == nullptr) 
        throw std::logic_error("Node is nullptr");
    if (node->prev != nullptr) 
        node->prev->next = node->next;
    else
        this->_head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        this->_tail = node->prev;

    delete node;
    this->_count--;
}



#endif