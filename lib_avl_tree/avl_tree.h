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
    AVLNode<TKey, TValue>* find_pos(const TKey& Key)const;
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
    //        G
    //       / \
    //      P   T3
    //     / \
    //    C   T2
    //       

    AVLNode<TKey, TValue>* G = node;        
    AVLNode<TKey, TValue>* P = G->left;     
    AVLNode<TKey, TValue>* T2 = P->right; 

    P->parent = G->parent;
    if (!G->parent)
        _root = P;
    else if (G->parent->left == G)
        G->parent->left = P;
    else
        G->parent->right = P;

    //         G
    //        / \
    //      T2  T3
    G->left = T2;
    if (T2)
        T2->parent = G;

    //         P
    //        / \
    //       C   G
    //          / \
    //         T2 T3
    P->right = G;
    G->parent = P;

    recalc_height(G);
    recalc_height(P);
}


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node)
{
    //        G
    //       / \
    //      T1  P
    //         / \
    //        T2  C

    AVLNode<TKey, TValue>* G = node;       
    AVLNode<TKey, TValue>* P = G->right;    
    AVLNode<TKey, TValue>* T2 = P->left;   

    P->parent = G->parent;
    if (!G->parent)
        _root = P;
    else if (G->parent->left == G)
        G->parent->left = P;
    else
        G->parent->right = P;

    //         G
    //        / \
    //      T1  T2
    G->right = T2;
    if (T2)
        T2->parent = G;

    //         P
    //        / \
    //       G   C
    //      / \
    //     T1 T2
    P->left = G;
    G->parent = P;

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
