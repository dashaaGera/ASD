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

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        if (curr == list.head()) {
            return true;
        }
    }
    return false;
}

#endif