#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include <string.h>
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

bool check_breckets(std::string s);

template <typename T>
bool has_cycle_hare_and_turtle(const List<T>& list) {
    if (list.head() == nullptr || list.head()->next == nullptr)
        return false;

    Node<T>* slow = list.head();
    Node<T>* fast = list.head();

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

template<typename T>
bool has_cycle_reverse_pointers(const List<T>& list) {
    if (list.is_empty()) return false;

    Node<T>* curr = list.head();
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
    bool is_cycle = false;

    while (curr != nullptr) {
        next = curr->next; //save pointer on next node
        curr->next = prev; //reverse pointer for curr node
        prev = curr; //move pointer on curr node
        curr = next; // jump next node befote reverse pointer
        if (curr == list.head()) {
            is_cycle = true;
        }
    }

    curr = list.head();

    while (curr != nullptr) {
        next = curr->next; //save pointer on next node
        curr->next = prev; //reverse pointer for curr node
        prev = curr; //move pointer on curr node
        curr = next; // jump next node befote reverse pointer
        if (curr == list.head()) {
            break;
        }
    }
    return is_cycle;
}

template <typename T>
Node<T>* has_cycle_problem_node(const List<T>& list) {
    if (list.head() == nullptr || list.head()->next == nullptr)
        return nullptr; 

    Node<T>* slow = list.head();
    Node<T>* fast = list.head();

    bool has_cycle = false;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle)
        return nullptr;

    slow = list.head();
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}


#endif