#include <iostream>
#include <stdexcept>
#include <sstream>
#include "../lib_tqueue/tqueue.h"
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
    : value(value_), left(left_), right(right_) {
}

template <typename TKey, typename TValue>
class BSTree {
    TreeNode<TKey, TValue>* _root;
    int _count;
    void clear_tree(TreeNode< TKey, TValue >* curr);
    TreeNode<TKey, TValue>* find_pos(const TKey& Key) const;
    TreeNode<TKey, TValue>* find_max_left(TreeNode<TKey, TValue>* node);
    TreeNode<TKey, TValue>* erase_node(TreeNode<TKey, TValue>* node, const TKey& Key);
    void to_string_sorted_rec(TreeNode<TKey, TValue>* curr, std::ostringstream& out) const;
public:
    BSTree();
    ~BSTree();
    TreeNode<TKey, TValue>* root() const;
    void insert(const TKey& Key, const TValue& Val);
    void erase(const TKey& Key);
    bool is_empty() const;
    TValue find(const TKey& Key) const;
    int size() const;
    std::string to_string() const;
    std::string to_string_sorted() const;
    
};
template <typename TKey, typename TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr), _count(0) {}

template <typename TKey, typename TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear_tree(_root);
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear_tree(TreeNode< TKey, TValue >* curr) {
    if (curr == nullptr) return;
    clear_tree(curr->left);
    clear_tree(curr->right);
    delete curr;
}

template <typename TKey, typename TValue>
bool BSTree<TKey, TValue>::is_empty() const {
    return _root == nullptr;
}

template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::root() const {
    return _root;
}

template <typename TKey, typename TValue>
int BSTree<TKey, TValue>::size() const {
    return _count;
}

template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_pos(const TKey& Key)const {
    TreeNode<TKey, TValue>* curr = _root;
    TreeNode<TKey, TValue>* prev = nullptr;
    while (curr != nullptr && curr->value.first != Key ) {
        prev = curr;
        if (curr->value.first > Key)
            curr = curr->left;
        else
            curr = curr->right;

    }
    return (curr !=nullptr) ? curr : prev ;
}


template <typename TKey, typename TValue>
TValue BSTree<TKey, TValue>::find(const TKey& Key) const {
    TreeNode<TKey, TValue>* found = find_pos(Key);
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
void BSTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    TreeNode<TKey, TValue>* found = find_pos(Key);
    if ((found && found->left && found->left->value.first == Key) ||
        (found && found->right && found->right->value.first == Key))
        throw std::logic_error("elem exist in the bstree");
    TreeNode<TKey, TValue>* node = new TreeNode<TKey, TValue>(std::pair<TKey, TValue>(Key, Val));
    if (is_empty()) {
        _root = node;
        _count++;
    }
    else if (found->value.first > Key)
    {
        found->left = node;
        _count++;
    }
        
    else {
        found->right = node;
        _count++;
    }

}
template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(TreeNode<TKey, TValue>* node) {
    if (node == nullptr || node->left == nullptr)
        return nullptr; 
    TreeNode<TKey, TValue>* current = node->left;
    while (current->right != nullptr) {
        current = current->right;  
    }
    return current;
}


template <typename TKey, typename TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::erase_node(TreeNode<TKey, TValue>* node,const TKey& Key) {
    if (node == nullptr)
        return nullptr;
    if (Key < node->value.first) {
        node->left = erase_node(node->left, Key);
    }
    else if (Key > node->value.first) {
        node->right = erase_node(node->right, Key);
    }
    else {
        if (node->left == nullptr) {
            TreeNode<TKey, TValue>* right_child = node->right;
            delete node;
            _count--;
            return right_child; 
        }

        else if (node->right == nullptr) {
            TreeNode<TKey, TValue>* left_child = node->left;
            delete node;
            _count--;
            return left_child;
        }

        else {
            TreeNode<TKey, TValue>* max_left = find_max_left(node);
            node->value = max_left->value;
            node->left = erase_node(node->left, max_left->value.first);
            return node;
        }
    }

    return node;
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& Key) {
    _root = erase_node(_root, Key);
}

template <typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string() const {
    if (_root == nullptr) {
        return "";
    }
    std::ostringstream out;

    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* cur = q.head();
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
std::string BSTree<TKey, TValue>::to_string_sorted() const {
    std::ostringstream out;
    to_string_sorted_rec(_root, out);
    return out.str();
}


template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::to_string_sorted_rec(TreeNode<TKey, TValue>* curr,
    std::ostringstream& out) const {
    if (curr == nullptr)
        return;
    to_string_sorted_rec(curr->left, out);
    out << curr->value.first << " ";
    to_string_sorted_rec(curr->right, out);
}