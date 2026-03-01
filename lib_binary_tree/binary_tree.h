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
    void print_depth_left_current_right_rec(TreeNode<TKey, TValue>* curr) const;
    void print_depth_current_left_right_rec(TreeNode<TKey, TValue>* curr) const;
    void print_depth_left_right_current_rec(TreeNode<TKey, TValue>* curr) const;
    void clear_tree(TreeNode< TKey, TValue >* curr);
public:
    Tree();
    ~Tree();
    TreeNode<TKey, TValue>* root() const;
    void insert(const TKey& Key, const TValue& Val);
    void erase(const TKey& Key);
    void print_depth_left_current_right() const ;
    void print_depth_current_left_right() const;
    void print_depth_left_right_current() const;
    void print_width() const;
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
void Tree<TKey, TValue>::print_width()const {
    if (_root == nullptr) {
        std::cout << "Empty tree" << std::endl;
        return;
    }

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* cur = q.head();
        q.pop();
        std::cout << "(" << cur->value.first << ", " << cur->value.second << ") ";
        if (cur->left != nullptr) {
            q.push(cur->left);
            nodesInNextLevel++;
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
            nodesInNextLevel++;
        }

        nodesInCurrentLevel--;
        if (nodesInCurrentLevel == 0) {
            std::cout << std::endl;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_current_right() const {
    print_depth_left_current_right_rec(_root);
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_current_left_right() const {
    print_depth_current_left_right_rec(_root);
}
template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_right_current() const {
    print_depth_left_right_current_rec(_root);
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_current_left_right_rec(TreeNode<TKey, TValue>* curr) const {
    if (curr == nullptr)
        return;
    std::cout << "(" << curr->value.first << ", " << curr->value.second << ") ";
    print_depth_current_left_right_rec(curr->left);
    print_depth_current_left_right_rec(curr->right);

}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_current_right_rec(TreeNode<TKey, TValue>* curr) const {
    if (curr == nullptr)
        return;
    print_depth_left_current_right_rec(curr->left);
    std::cout << "(" << curr->value.first << ", " << curr->value.second << ") ";
    print_depth_left_current_right_rec(curr->right);

}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::print_depth_left_right_current_rec(TreeNode<TKey, TValue>* curr) const {
    if (curr == nullptr)
        return;
    print_depth_left_right_current_rec(curr->left);
    print_depth_left_right_current_rec(curr->right);
    std::cout << "(" << curr->value.first << ", " << curr->value.second << ") ";
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    TreeNode<TKey, TValue>* node = new  TreeNode<TKey, TValue>(std::make_pair(Key, Val), nullptr, nullptr);
    if (is_empty()) {
        _root = node;
        _count++;
        return;
    }

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    TreeNode<TKey, TValue>* cur = nullptr;
    while (true) {
        cur = q.head();
        q.pop();
        if (cur->left==nullptr) {
            cur->left = node;
            _count++;
            return;
        }
        else if (cur->right==nullptr) {
            cur->right = node;
            _count++;
            return;
        }
        q.push(cur->left);
        q.push(cur->right);
    }
}

template <typename TKey, typename TValue>
void Tree<TKey, TValue>::erase(const TKey& Key) {
    if (is_empty()) return;

    if (_root->left == nullptr && _root->right == nullptr) {
        if (_root->value.first == Key) {
            delete _root;
            _root = nullptr;
            _count--;
        }
        return;
    }

    // find erase node and last node 
    TreeNode<TKey, TValue>* nodeToDelete = nullptr;
    TreeNode<TKey, TValue>* lastNode = nullptr;
    TreeNode<TKey, TValue>* lastNodeParent = nullptr;

    Queue<TreeNode<TKey, TValue>*> nodeQueue;
    Queue<TreeNode<TKey, TValue>*> parentQueue;

    nodeQueue.push(_root);
    parentQueue.push(nullptr);

    while (!nodeQueue.is_empty()) {
        TreeNode<TKey, TValue>* curr = nodeQueue.head();
        TreeNode<TKey, TValue>* parent = parentQueue.head();

        nodeQueue.pop();
        parentQueue.pop();

        lastNode = curr;
        lastNodeParent = parent;

        if (curr->value.first == Key) {
            nodeToDelete = curr;
        }

        if (curr->left != nullptr) {
            nodeQueue.push(curr->left);
            parentQueue.push(curr);
        }
        if (curr->right != nullptr) {
            nodeQueue.push(curr->right);
            parentQueue.push(curr);
        }
    }

    if (nodeToDelete == nullptr) return;

    if (nodeToDelete == lastNode) {
        if (lastNodeParent == nullptr) {
            delete _root;
            _root = nullptr;
        }
        else {
            if (lastNodeParent->left == lastNode) {
                lastNodeParent->left = nullptr;
            }
            else {
                lastNodeParent->right = nullptr;
            }
            delete lastNode;
        }
        _count--;
        return;
    }

    nodeToDelete->value = lastNode->value;

    
        if (lastNodeParent->left == lastNode) {
            lastNodeParent->left = nullptr;
        }
        else {
            lastNodeParent->right = nullptr;
        }
        delete lastNode;
        _count--;
    
}

template <typename TKey, typename TValue>
TValue Tree<TKey, TValue>::find(const TKey& Key) const {
    if (is_empty()) {
        throw std::logic_error("Tree is empty");
    }

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* curr = q.head();
        q.pop();

        if (curr->value.first == Key) {
            return curr->value.second; 
        }

        if (curr->left != nullptr) {
            q.push(curr->left);
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
        }
    }

    throw std::logic_error("Key not found");;
}


#endif