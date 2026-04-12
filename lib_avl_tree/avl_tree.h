#pragma once
#include "../lib_bstree/bstree.h"
#include <iostream>
#include <stdexcept>
#include< algorithm >
#include "../lib_tqueue/tqueue.h"

template <typename TKey, typename TValue>
struct AVLNode {
    std::pair<TKey, TValue> value;
    AVLNode<TKey, TValue>* left;
    AVLNode<TKey, TValue>* right;
    int height;
    AVLNode<TKey, TValue>* parent;
    AVLNode(std::pair<TKey, TValue> value_ = std::pair<TKey, TValue>(),AVLNode<TKey, TValue>* parent_ =nullptr, 
        AVLNode<TKey, TValue>* left_ = nullptr,
        AVLNode<TKey, TValue>* right_ = nullptr, int height_=1);
};

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>::AVLNode(std::pair<TKey, TValue> value_ , AVLNode<TKey, TValue>* parent_,
    AVLNode<TKey, TValue>* left_ ,
    AVLNode<TKey, TValue>* right_ , int height_ )
    : value(value_), parent(parent_) ,left(left_), right(right_), height(height_) {}

template <typename TKey, typename TValue>
class AVLTree {
    AVLNode<TKey, TValue>* _root;
    int _count;
public:
    AVLTree() : _root(nullptr), _count(0) {};
    ~AVLTree();
    AVLNode<TKey, TValue>* root() const;
    void insert(const TKey& Key, const TValue& Val);
    void erase(const TKey& Key);
    bool is_empty() const;
    TValue find(const TKey& Key) const;
    int size() const;
    void print_tree() const;
    std::string to_string_sorted() const;
    std::string to_string() const;
private:
    void clear_tree(AVLNode< TKey, TValue >* curr);
    void right_rotate(AVLNode<TKey, TValue>* node);
    void left_rotate(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RR(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    int calculate_balance(AVLNode<TKey, TValue>* node);
    void recalc_height(AVLNode<TKey, TValue>* node);
    void restore_balance(AVLNode<TKey, TValue>* node);
    AVLNode<TKey, TValue>* insert_node(const TKey& Key, const TValue& Val);
    AVLNode<TKey, TValue>* erase_node(AVLNode<TKey, TValue>* node);
    AVLNode<TKey, TValue>* find_pos(const TKey& Key)const;
    AVLNode<TKey, TValue>* find_max_left(AVLNode<TKey, TValue>* node);
    void print_tree_rec(AVLNode<TKey, TValue>* node, std::string prefix, bool is_last) const;
    void to_string_sorted_rec(AVLNode<TKey, TValue>* curr,
        std::ostringstream& out) const;

};

template <typename TKey, typename TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear_tree(_root);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::clear_tree(AVLNode< TKey, TValue >* curr) {
    if (curr == nullptr) return;
    clear_tree(curr->left);
    clear_tree(curr->right);
    delete curr;
}

template <typename TKey, typename TValue>
bool AVLTree<TKey, TValue>::is_empty() const {
    return _root == nullptr;
}

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::root() const {
    return _root;
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::size() const {
    return _count;
}

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_pos(const TKey& Key)const {
    AVLNode<TKey, TValue>* curr = _root;
    AVLNode<TKey, TValue>* prev = nullptr;
    while (curr != nullptr && curr->value.first != Key) {
        prev = curr;
        if (curr->value.first > Key)
            curr = curr->left;
        else
            curr = curr->right;

    }
    return (curr != nullptr) ? curr : prev;
}

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_max_left(AVLNode<TKey, TValue>* node) {
    if (node == nullptr || node->left == nullptr)
        return nullptr;
    AVLNode<TKey, TValue>* current = node->left;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

template <typename TKey, typename TValue>
TValue AVLTree<TKey, TValue>::find(const TKey& Key) const {
    AVLNode<TKey, TValue>* found = find_pos(Key);
    if (found == nullptr)
        throw std::logic_error("elem not found");

    if (found->value.first == Key)
        return found->value.second;

    if (found->left && found->left->value.first == Key)
        return found->left->value.second;

    if (found->right && found->right->value.first == Key)
        return found->right->value.second;

    throw std::logic_error("elem not found");
}

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::insert_node(const TKey& Key, const TValue& Val) {
    AVLNode<TKey, TValue>* found = find_pos(Key);
    if ((found && found->left && found->left->value.first == Key) ||
        (found && found->right && found->right->value.first == Key))
        throw std::logic_error("elem exist in the bstree");

    AVLNode<TKey, TValue>* node = new AVLNode<TKey, TValue>(std::pair<TKey, TValue>(Key, Val));

    if (is_empty()) {
        _root = node;
        _count++;
        return node;
    }

    if (found->value.first > Key) {
        found->left = node;
        node->parent = found;
        _count++;
    }
    else if (found->value.first < Key) {
        found->right = node;
        node->parent = found;
        _count++;
    }

    return node;
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node)
{
    //     GG  GG    
    //       \ /            GG  GG
    //        G              \ /
    //       /      ->        P
    //      P               /   \        
    //     / \             C     G
    //    C   T                 /
    //                         T

    AVLNode<TKey, TValue>* G = node;        
    AVLNode<TKey, TValue>* P = G->left;
    AVLNode<TKey, TValue>* C = P->left;
    AVLNode<TKey, TValue>* T = P->right; 
    AVLNode<TKey, TValue>* GG = node->parent;

    G->left = T;
    if (T) T->parent = G;

    P->right = G;
    G->parent = P;
    if (GG) {
        if (GG->left == G)
            GG->left = P;
        else
            GG->right = P;
    }
    else
        _root = P;

    P->parent = GG;

    recalc_height(G);
    recalc_height(P);
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node)
{
    //     GG  GG 
    //      \ /           GG     GG
    //       G              \   /
    //        \               P
    //          P       ->   / \
    //         / \          G   C
    //        T   C          \
    //                        T

    AVLNode<TKey, TValue>* G = node;       
    AVLNode<TKey, TValue>* P = G->right;    
    AVLNode<TKey, TValue>* T = P->left; 
    AVLNode<TKey, TValue>* GG = G->parent;

    G->right = T;
    if (T) T->parent = G;

    P->left = G;
    G->parent = P;

    if (GG) {
        if (GG->left == G)
            GG->left = P;
        else
            GG->right = P;
    }
    else {
        _root = P;
    }
    P->parent = GG;

    recalc_height(G);
    recalc_height(P);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->left;
    AVLNode<TKey, TValue>* C = P->right;
    //    G           G
    //   /           /
    //  P     ->    C     ->   C
    //   \         /         /   \
    //    C       P         P     G

    left_rotate(P);
    right_rotate(G);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->right;
    AVLNode<TKey, TValue>* C = P->left;
    //    G           G
    //     \           \
    //      P     ->    C     ->     C
    //     /             \         /   \
    //   C                P       G     P

    right_rotate(P);
    left_rotate(G);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    //    G
    //     \           
    //       P     ->     P
    //        \         /   \
    //         C       G     C

    left_rotate(G);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    //     G
    //    /
    //   P    ->    P
    //  /         /   \
    // C         C     G

    right_rotate(G);
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::calculate_balance(AVLNode<TKey, TValue>* node) {
    int left_height = node->left ? node->left->height : 0;
    int right_height = node->right ? node->right->height : 0;
    return right_height - left_height;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    int left_height = node->left ? node->left->height : 0;
    int right_height = node->right ? node->right->height : 0;
    node->height = std::max(left_height, right_height) + 1;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::restore_balance(AVLNode<TKey, TValue>* node)
{
    if (!node) return;
    int balance = calculate_balance(node);
    if (balance < -1)
    {
        if (calculate_balance(node->left) <= 0)
            LL(node);
        else
            LR(node);
    }
    else if (balance > 1)
    {
        if (calculate_balance(node->right) >= 0)
            RR(node);
        else
            RL(node);
    }
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val)
{
    AVLNode<TKey, TValue>* C = insert_node(Key, Val);
    AVLNode<TKey, TValue>* cur = C->parent;

    while (cur != nullptr)
    {
        recalc_height(cur);
        int balance = calculate_balance(cur);
        if (std::abs(balance) > 1)
            restore_balance(cur);
        cur = cur->parent;
    }
}

//return parent 
template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::erase_node(AVLNode<TKey, TValue>* node) {
   
    // 1) node is sheet
    if (node->left == nullptr && node->right == nullptr) {
        AVLNode<TKey, TValue>* parent = node->parent;
        if (parent) {
            if (parent->left == node)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
        else 
            _root = nullptr;
        delete node;
        _count--;

        return parent;
    }

    //2) node has only a left child
    else if (node->left != nullptr && node->right == nullptr) {
        AVLNode<TKey, TValue>* parent = node->parent;
        AVLNode<TKey, TValue>* child = node->left;  

        if (parent) {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else {
            _root = child;
        }
        child->parent = parent;
        delete node;
        _count--;
        return parent;
    }

    //3) node has only a right child
    else if (node->left == nullptr && node->right != nullptr) {
        AVLNode<TKey, TValue>* parent = node->parent;
        AVLNode<TKey, TValue>* child = node->right; 

        if (parent) {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else {
            _root = child;
        }

        child->parent = parent;
        delete node;
        _count--;
        return parent;
    }

    //4) node has both child‰ÛÚ

    else {
        AVLNode<TKey, TValue>* max_left = find_max_left(node);
        node->value = max_left->value;
        AVLNode<TKey, TValue>* parent_of_max_left = max_left->parent;

        AVLNode<TKey, TValue>* left_child = max_left->left;

        if (parent_of_max_left->left == max_left) {
            parent_of_max_left->left = left_child;
        }
        else {
            parent_of_max_left->right = left_child;
        }

        if (left_child) {
            left_child->parent = parent_of_max_left;
        }

        delete max_left;
        _count--;

        return parent_of_max_left;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::erase(const TKey& Key) {
    AVLNode<TKey, TValue>* node_to_delete = find_pos(Key);
    if (!node_to_delete || node_to_delete->value.first != Key)
        throw std::logic_error("elem not found");
    AVLNode<TKey, TValue>* real_delete_node_parent = erase_node(node_to_delete);
    AVLNode<TKey, TValue>* cur = real_delete_node_parent;
    while (cur) {
        int balance = calculate_balance(cur);
        if (std::abs(balance) > 1)
            restore_balance(cur);

        int old_height = cur->height;
        recalc_height(cur);
        if (old_height == cur->height)
            break;

        cur = cur->parent;
    }
}

template <typename TKey, typename TValue>
std::string AVLTree<TKey, TValue>::to_string_sorted() const {
    std::ostringstream out;
    to_string_sorted_rec(_root, out);
    return out.str();
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::to_string_sorted_rec(AVLNode<TKey, TValue>* curr,
    std::ostringstream& out) const {
    if (curr == nullptr)
        return;
    to_string_sorted_rec(curr->left, out);
    out << curr->value.first << " ";
    to_string_sorted_rec(curr->right, out);
}


template <typename TKey, typename TValue>
std::string AVLTree<TKey, TValue>::to_string() const {
    if (_root == nullptr) {
        return "";
    }
    std::ostringstream out;

    Queue<AVLNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        AVLNode<TKey, TValue>* cur = q.head();
        q.pop();
        out << cur->value.first << " ";
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
    }
    return out.str();
}



template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::print_tree() const
{
    if (_root == nullptr) {
        std::cout << "Empty tree\n";
        return;
    }
    print_tree_rec(_root, "", true);
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::print_tree_rec(AVLNode<TKey, TValue>* node, std::string prefix, bool is_last) const {
    if (!node) return;
    std::cout << prefix;

    if (!prefix.empty()) {
        std::cout << (is_last ? "|__" : "|--");
    }


    std::cout << "(" << node->value.first << ", " << node->value.second << ", " <<node->height<< ")\n";

    std::string new_prefix = prefix + (is_last ? "    " : "|   ");

    if (node->right)
        print_tree_rec(node->right, new_prefix, node->left == nullptr);

    if (node->left)
        print_tree_rec(node->left, new_prefix, true);
}
