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
    if (list.tail()->next == list.head()) {
        return true;
    }
    Node<T>* curr = list.head();
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
    bool cycle_found = false;
    while (curr != nullptr) {
        next = curr->next; //save pointer on next node
        curr->next = prev; //reverse pointer for curr node
        prev = curr; //move pointer on curr node
        curr = next; // jump next node befote reverse pointer
        if (curr == list.head()) {
            cycle_found = true;
            break;
        }
    }
    Node<T>* restore_curr = prev;
    Node<T>* restore_prev = nullptr;
    Node<T>* restore_next = nullptr;

    while (restore_curr != nullptr) {
        restore_next = restore_curr->next;
        restore_curr->next = restore_prev;
        restore_prev = restore_curr;
        restore_curr = restore_next;
    }

    if (cycle_found)
        curr->next = restore_prev; //head reverse to second node
    return cycle_found;
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


template <typename T>
void destroy_list_cycle(const List<T>& list) {
    Node<T>* problem_node = has_cycle_problem_node(list);
    if (problem_node == nullptr)
        return;
    Node<T>* curr = problem_node;
    Node<T>* prev = curr;
    while (prev->next != nullptr) {
        prev = curr;
        curr = curr->next;
        if (prev->next == problem_node)
            prev->next = nullptr;
    }
}


#endif