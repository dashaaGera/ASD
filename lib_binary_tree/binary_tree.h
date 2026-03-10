#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <stdexcept>
#include "../lib_tqueue/tqueue.h"
#include <utility> 

template <typename TKey, typename TValue>
struct TreeNode {
    std::pair<TKey, TValue> value;
    TreeNode<TKey, TValue>* left;
    TreeNode<TKey, TValue>* right;
    TreeNode(std::pair<TKey, TValue> value_ = std::pair<TKey, TValue>(), TreeNode<TKey, TValue>* left_ = nullptr,
        TreeNode<TKey, TValue>* right_ = nullptr);
};

template <typename TKey, typename TValue>
TreeNode<TKey, TValue>::TreeNode(std::pair<TKey, TValue> value_, TreeNode<TKey, TValue>* left_, TreeNode<TKey, TValue>* right_)
    : value(value_), left(left_), right(right_){}

template <typename TKey, typename TValue>
class Tree {
    TreeNode<TKey, TValue>* _root;
    int _count;
    void print_depth_left_current_right_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const;
    void print_depth_current_left_right_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const;
    void print_depth_left_right_current_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const;
    void clear_tree(TreeNode< TKey, TValue >* curr);
    TreeNode<TKey, TValue>* find_node(const TKey& key) const;
    TreeNode<TKey, TValue>* find_last_node() const;
    TreeNode<TKey, TValue>* find_parent(TreeNode<TKey, TValue>* node) const;
public:
    Tree();
    ~Tree();
    TreeNode<TKey, TValue>* root() const;
    void insert(const TKey& Key, const TValue& Val);
    void erase(const TKey& Key);
    void print_depth_left_current_right(std::ostream& out) const ;
    void print_depth_current_left_right(std::ostream& out) const;
    void print_depth_left_right_current(std::ostream& out) const;
    void print_width(std::ostream& out) const;
    bool is_empty() const;
    TValue find(const TKey& Key) const;
    int size() const;
};

template <typename TKey, typename TValue>
Tree<TKey, TValue>::Tree(): _root(nullptr),_count(0) {}

template <typename TKey, typename TValue>
Tree<TKey, TValue>::~Tree(){
    clear_tree(_root);
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::clear_tree(TreeNode< TKey, TValue >* curr) {
    if (curr == nullptr) return;
    clear_tree(curr->left);
    clear_tree(curr->right);
    delete curr;
}

template <typename TKey, typename TValue>
bool Tree<TKey, TValue>::is_empty() const{
    return _root == nullptr;
}

template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::root() const {
    return _root;
}

template <typename TKey, typename TValue>
int Tree<TKey, TValue>::size() const {  
    return _count;
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_width(std::ostream& out) const {
    if (_root == nullptr) {
        out << "Empty tree\n";
        return;
    }

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* cur = q.head();
        q.pop();

        out << "(" << cur->value.first << ", " << cur->value.second << ") ";

        if (cur->left) {
            q.push(cur->left);
            nodesInNextLevel++;
        }

        if (cur->right) {
            q.push(cur->right);
            nodesInNextLevel++;
        }

        nodesInCurrentLevel--;

        if (nodesInCurrentLevel == 0) {
            out << "\n";
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_current_right(std::ostream& out) const {
    print_depth_left_current_right_rec(_root,out);
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_current_left_right(std::ostream& out) const {
    print_depth_current_left_right_rec(_root,out);
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_right_current(std::ostream& out) const {
    print_depth_left_right_current_rec(_root,out);
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_current_left_right_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const {
    if (curr == nullptr)
        return;
    out << "(" << curr->value.first << ", " << curr->value.second << ") ";
    print_depth_current_left_right_rec(curr->left,out);
    print_depth_current_left_right_rec(curr->right,out);

}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_current_right_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const {
    if (curr == nullptr)
        return;
    print_depth_left_current_right_rec(curr->left, out);
    out << "(" << curr->value.first << ", " << curr->value.second << ") ";
    print_depth_left_current_right_rec(curr->right,out);

}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_right_current_rec(TreeNode<TKey, TValue>* curr, std::ostream& out) const {
    if (curr == nullptr)
        return;
    print_depth_left_right_current_rec(curr->left, out);
    print_depth_left_right_current_rec(curr->right, out);
    out << "(" << curr->value.first << ", " << curr->value.second << ") ";
}


template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_node(const TKey& key) const {
    if (_root == nullptr) return nullptr;
    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* curr = q.head();
        q.pop();
        if (curr->value.first == key)
            return curr;
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    return nullptr;
}

template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_last_node() const {
    if (_root == nullptr) return nullptr;
    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    TreeNode<TKey, TValue>* last = nullptr;

    while (!q.is_empty()) {
        last = q.head();
        q.pop();

        if (last->left) q.push(last->left);
        if (last->right) q.push(last->right);
    }

    return last;
}
template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_parent(TreeNode<TKey, TValue>* node) const {
    if (_root == nullptr || _root == node) return nullptr;

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* curr = q.head();
        q.pop();
        if (curr->left == node || curr->right == node)
            return curr;

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }

    return nullptr;
}

template <typename TKey, typename TValue>
TValue Tree<TKey, TValue>::find(const TKey& Key) const {
    TreeNode<TKey, TValue>* node = find_node(Key);
    if (node == nullptr)
        throw std::logic_error("Key not found");

    return node->value.second;
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    TreeNode<TKey, TValue>* node =
        new TreeNode<TKey, TValue>(std::make_pair(Key, Val), nullptr, nullptr);
    if (_root == nullptr) {
        _root = node;
        _count++;
        return;
    }
    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* cur = q.head();
        q.pop();
        if (cur->left==nullptr) {
            cur->left = node;
            break;
        }

        if (cur->right == nullptr) {
            cur->right = node;
            break;
        }

        q.push(cur->left);
        q.push(cur->right);
    }

    _count++;
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::erase(const TKey& Key) {
    if (_root == nullptr) return;
    TreeNode<TKey, TValue>* nodeToDelete = find_node(Key);
    if (nodeToDelete==nullptr) return;
    TreeNode<TKey, TValue>* lastNode = find_last_node();
    nodeToDelete->value = lastNode->value;
    TreeNode<TKey, TValue>* parent = find_parent(lastNode);

    if (parent!=nullptr) {
        if (parent->left == lastNode)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }
    else {
        _root = nullptr;
    }

    delete lastNode;
    _count--;
}
#endif