#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "../lib_tqueue/tqueue.h"

enum class RBColor { RED, BLACK};
inline std::ostream& operator<<(std::ostream& os, RBColor color) {
    switch (color) {
    case RBColor::RED:         os << "RED"; break;
    case RBColor::BLACK:       os << "BLACK"; break;
    default:                   os << "UNKNOWN";
    }
    return os;
}

template <typename TKey, typename TValue>
struct RBNode {
    std::pair<TKey, TValue> value;
    RBNode<TKey, TValue>* left;
    RBNode<TKey, TValue>* right;
    RBNode<TKey, TValue>* parent;
    RBColor color;
    RBNode(std::pair<TKey, TValue> value_ = std::pair<TKey, TValue>(), RBNode<TKey, TValue>* parent_ = nullptr,
        RBNode<TKey, TValue>* left_ = nullptr,
        RBNode<TKey, TValue>* right_ = nullptr, RBColor color_ = RBColor::RED);
};

template <typename TKey, typename TValue>
RBNode<TKey, TValue>::RBNode(std::pair<TKey, TValue> value_, RBNode<TKey, TValue>* parent_,
    RBNode<TKey, TValue>* left_,
    RBNode<TKey, TValue>* right_, RBColor color_ )
    : value(value_), parent(parent_), left(left_), right(right_), color(color_) {
}

template <typename TKey, typename TValue>
class RBTree {
    RBNode<TKey, TValue>* _root;
    int _count;
public:
    RBTree() : _root(nullptr), _count(0) {};
    ~RBTree();
    RBNode<TKey, TValue>* root() const;
    void insert(const TKey& Key, const TValue& Val);
    void erase(const TKey& Key);
    bool is_empty() const;
    TValue find(const TKey& Key) const;
    int size() const;
    void print_tree() const;
    std::string to_string_sorted() const;
    std::string to_string() const;
private:
    void clear_tree(RBNode< TKey, TValue >* curr);
    void right_rotate(RBNode<TKey, TValue>* node);
    void left_rotate(RBNode<TKey, TValue>* node);
    void restore_balance(RBNode<TKey, TValue>* node);
    void swap_colors(RBNode<TKey, TValue>* node1, RBNode<TKey, TValue>* node2);
    void recolor(RBNode<TKey, TValue>* node);
    std::pair<RBNode<TKey, TValue>*, RBColor> erase_node(RBNode<TKey, TValue>* node);
    void fix_double_black(RBNode<TKey, TValue>* node);
    RBNode<TKey, TValue>* insert_node(const TKey& Key, const TValue& Val);
    RBNode<TKey, TValue>* find_pos(const TKey& Key)const;
    RBNode<TKey, TValue>* find_max_left(RBNode<TKey, TValue>* node);
    void print_tree_rec(RBNode<TKey, TValue>* node, std::string prefix, bool is_last) const;
    void to_string_sorted_rec(RBNode<TKey, TValue>* curr,
        std::ostringstream& out) const;

};

template <typename TKey, typename TValue>
RBTree<TKey, TValue>::~RBTree() {
    clear_tree(_root);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::clear_tree(RBNode< TKey, TValue >* curr) {
    if (curr == nullptr) return;
    clear_tree(curr->left);
    clear_tree(curr->right);
    delete curr;
}

template <typename TKey, typename TValue>
bool RBTree<TKey, TValue>::is_empty() const {
    return _root == nullptr;
}

template <typename TKey, typename TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::root() const {
    return _root;
}

template <typename TKey, typename TValue>
int RBTree<TKey, TValue>::size() const {
    return _count;
}

template <typename TKey, typename TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_pos(const TKey& Key)const {
    RBNode<TKey, TValue>* curr = _root;
    RBNode<TKey, TValue>* prev = nullptr;
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
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_max_left(RBNode<TKey, TValue>* node) {
    if (node == nullptr || node->left == nullptr)
        return nullptr;
    RBNode<TKey, TValue>* current = node->left;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

template <typename TKey, typename TValue>
TValue RBTree<TKey, TValue>::find(const TKey& Key) const {
    RBNode<TKey, TValue>* found = find_pos(Key);
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
RBNode<TKey, TValue>* RBTree<TKey, TValue>::insert_node(const TKey& Key, const TValue& Val) {
    RBNode<TKey, TValue>* found = find_pos(Key);
    if ((found && found->left && found->left->value.first == Key) ||
        (found && found->right && found->right->value.first == Key))
        throw std::logic_error("elem exist in the bstree");

    RBNode<TKey, TValue>* node = new RBNode<TKey, TValue>(std::pair<TKey, TValue>(Key, Val));

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
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node)
{
    //     GG  GG    
    //       \ /            GG  GG
    //        G              \ /
    //       /      ->        P
    //      P               /   \        
    //     / \             C     G
    //    C   T                 /
    //                         T

    RBNode<TKey, TValue>* G = node;
    RBNode<TKey, TValue>* P = G->left;
    RBNode<TKey, TValue>* C = P->left;
    RBNode<TKey, TValue>* T = P->right;
    RBNode<TKey, TValue>* GG = node->parent;

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

}


template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node)
{
    //     GG  GG 
    //      \ /           GG     GG
    //       G              \   /
    //        \               P
    //          P       ->   / \
    //         / \          G   C
    //        T   C          \
    //                        T

    RBNode<TKey, TValue>* G = node;
    RBNode<TKey, TValue>* P = G->right;
    RBNode<TKey, TValue>* T = P->left;
    RBNode<TKey, TValue>* GG = G->parent;

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

}
template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::recolor(RBNode<TKey, TValue>* node) {
    if (node == nullptr) return;

    if (node->color == RBColor::RED) 
        node->color = RBColor::BLACK;
    else 
        node->color = RBColor::RED;
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::swap_colors(RBNode<TKey, TValue>* node1, RBNode<TKey, TValue>* node2) {
    if (node1 == nullptr || node2 == nullptr) return;

    RBColor tmp = node1->color;
    node1->color = node2->color;
    node2->color = tmp;
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::restore_balance(RBNode<TKey, TValue>* node) {
    if (node == nullptr) return;

    
    RBNode<TKey, TValue>* C = node;
    RBNode<TKey, TValue>* P = C->parent;
    RBNode<TKey, TValue>* G = P->parent;

    RBNode<TKey, TValue>* U = (G->right == P) ? G->left : G->right;

    if (U != nullptr && U->color == RBColor::RED) {
        recolor(P);
        recolor(U);
    //      ...                  ....
    //      [G]                  [G]
    //      /  \                /   \
    //    (U)   (P)     ->    [U]   [P]   
    //    ...   / \           ...   /  \
    //       ...  (C)              ... (C)   
        
        if (G == _root) return;
        recolor(G);

    //      ...                  
    //      (G)                 
    //      /  \                
    //    [U]   [P]       
    //    ...   / \           
    //       ...  (C)             
        RBNode<TKey, TValue>* GG = G->parent;
        if (GG != nullptr && GG->color == RBColor::RED) 
            restore_balance(G);  
        return;
         
                   
    }



    if (G->right == P && P->right == C) {
        left_rotate(G);
        swap_colors(P, G);

    //   [G]
    //   / \           
    //[U]   (P)     ->   (P)   ->       [P]
    //        \         /   \          /   \
    //        (C)      [G]   (C)    (G)    (C)
    //                 /            /  
    //                [U]         [U]
    }
    else if (G->right == P && P->left == C) {
        right_rotate(P);
        left_rotate(G);
        swap_colors(C, G);
        //     [G]               (C)              [C]
        //   /     \           /     \           /  \
        //  [U]    (P)  ->    [G]    (P)   ->   (G)  (P)
        //         /          /                /
        //       (C)         [U]             [U]
    }
    else if (G->left == P && P->left == C) {
        right_rotate(G);
        swap_colors(P, G);
        //     [G]            (P)           [P]
        //    /   \           /  \          /  \
        //   (P)  [U]  ->   (C)   [G]  ->  (C)  (G)
        //   /                      \            \
        //  (C)                     [U]          [U]
    }
    else if (G->left == P && P->right == C) {
        left_rotate(P);
        right_rotate(G);
        swap_colors(C, G);
        //    [G]           (C)          [C]
        //    /  \         /   \         /  \
        //   (P)  [U]  ->  (P)  [G]  -> (P)  (G)
        //     \                  \           \
        //     (C)               [U]          [U]
    } 
}


template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    RBNode<TKey, TValue>* node = insert_node(Key, Val);
    if (_root == node) {
        recolor(node);
        return;
    }

    if (node->parent->color == RBColor::BLACK) 
        return;

    restore_balance(node);
}


template <typename TKey, typename TValue>
std::pair<RBNode<TKey, TValue>*, RBColor>
RBTree<TKey, TValue>::erase_node(RBNode<TKey, TValue>* node) {

    RBColor deleted_color = node->color;

    // no children
    if (!node->left && !node->right) {
        RBNode<TKey, TValue>* parent = node->parent;

        if (parent) {
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else {
            _root = nullptr;
        }

        delete node;
        _count--;

        return { nullptr, deleted_color };
    }

    //1 child
    if (!node->left || !node->right) {
        RBNode<TKey, TValue>* child = node->left ? node->left : node->right;
        RBNode<TKey, TValue>* parent = node->parent;

        if (parent) {
            if (parent->left == node) parent->left = child;
            else parent->right = child;
        }
        else {
            _root = child;
        }

        child->parent = parent;

        delete node;
        _count--;

        return { child, deleted_color };
    }

    // 2 children
    RBNode<TKey, TValue>* pred = find_max_left(node);
    node->value = pred->value;

    return erase_node(pred);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::fix_double_black(RBNode<TKey, TValue>* node) {
    //node-double black
    while (node != _root) {
        RBNode<TKey, TValue>* parent = node->parent;
        if (!parent) break;

        RBNode<TKey, TValue>* sibling =
            (node == parent->left) ? parent->right : parent->left;
        if (!sibling) {
            node = parent;
            continue;
        }

        // 1) sibling - red+
        //    P(B)
        //    / \
        //  node  S(R)
        //         / \
        //        B  B
        if (sibling && sibling->color == RBColor::RED) {
            swap_colors(parent, sibling);

            if (node == parent->left)
                left_rotate(parent);
            else
                right_rotate(parent);
        //        S(B)
        //        / \
        //       P(R) B
        //        /
        //      node
        // case - S-black
            continue;
        }

        // 2) sibling -black and his children -black+
        //    P(B)
        //    / \
        //  node S(B)
        //         / \
        //        B   B
        if ((!sibling->left || sibling->left->color == RBColor::BLACK) &&
            (!sibling->right || sibling->right->color == RBColor::BLACK)) {

            sibling->color = RBColor::RED;
                // P(? )
                // / \
                //B   S(R)

            if (parent->color == RBColor::RED) {
                parent->color = RBColor::BLACK;
                break;
            }
            else {
                node = parent;
                continue;
            }
        }

        // 3) S- black CS - red +
        //     P
        //    / \
        //  node  S(B)
        //         /
        //         R
        if (node == parent->left) {
            if (!sibling->right || sibling->right->color == RBColor::BLACK) {
                if (sibling->left)
                    sibling->left->color = RBColor::BLACK;
                sibling->color = RBColor::RED;
                right_rotate(sibling);
                sibling = parent->right;
            }

         //        P
         //       / \
         //      node  R
         //             \
         //             S

            sibling->color = parent->color;
            parent->color = RBColor::BLACK;
            if (sibling->right)
                sibling->right->color = RBColor::BLACK;
            left_rotate(parent);
        //        R
        //       / \
        //      P    S
        //      /
        //     B
        }
        else {
        //         P
        //        / \
        //       S(B) node
        //        \
        //          R
            if (!sibling->left || sibling->left->color == RBColor::BLACK) {
                if (sibling->right)
                    sibling->right->color = RBColor::BLACK;
                sibling->color = RBColor::RED;
                left_rotate(sibling);
                sibling = parent->left;
            }

        //        P
        //       / \
        //       R   node
        //      /
        //      S
                 
            sibling->color = parent->color;
            parent->color = RBColor::BLACK;
            if (sibling->left)
                sibling->left->color = RBColor::BLACK;
            right_rotate(parent);
        //         R
        //        / \
        //       S   P
        //        \
        //         B
        }

        break;
    }

    if (node) node->color = RBColor::BLACK;
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::erase(const TKey& Key) {

    RBNode<TKey, TValue>* node = find_pos(Key);

    if (!node || node->value.first != Key)
        throw std::logic_error("not found");

    RBNode<TKey, TValue>* parent = node->parent;
    bool was_left = (parent && parent->left == node);

    auto [replacer, deleted_color] = erase_node(node);

    if (!replacer) {
        if (deleted_color == RBColor::BLACK && parent) {
            RBNode<TKey, TValue>* fake = new RBNode<TKey, TValue>(std::pair<TKey, TValue>(), parent, nullptr, nullptr, RBColor::BLACK);
            if (was_left)
                parent->left = fake;
            else
                parent->right = fake;

            fix_double_black(fake);

            RBNode<TKey, TValue>* p = fake->parent;
            if (p) {
                if (p->left == fake) p->left = nullptr;
                else if (p->right == fake) p->right = nullptr;
            }
            else {
                _root = nullptr;
            }
            delete fake;
            return;
        }

        if (_root) _root->color = RBColor::BLACK;
        return;
    }

    if (deleted_color == RBColor::RED) //+
        return;
     //    B
     //    /
     //  (R) < -deleted

    if (replacer && replacer->color == RBColor::RED) { //+
        replacer->color = RBColor::BLACK;
        return;
    }
    //    B
    //    /
    //   B < -deleted
    //   /
    //   R < -replacer

    fix_double_black(replacer);
}

template <typename TKey, typename TValue>
std::string RBTree<TKey, TValue>::to_string_sorted() const {
    std::ostringstream out;
    to_string_sorted_rec(_root, out);
    return out.str();
}


template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::to_string_sorted_rec(RBNode<TKey, TValue>* curr,
    std::ostringstream& out) const {
    if (curr == nullptr)
        return;
    to_string_sorted_rec(curr->left, out);
    out << curr->value.first << " ";
    to_string_sorted_rec(curr->right, out);
}


template <typename TKey, typename TValue>
std::string RBTree<TKey, TValue>::to_string() const {
    if (_root == nullptr) {
        return "";
    }
    std::ostringstream out;

    Queue<RBNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        RBNode<TKey, TValue>* cur = q.head();
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
void RBTree<TKey, TValue>::print_tree() const
{
    if (_root == nullptr) {
        std::cout << "Empty tree\n";
        return;
    }
    print_tree_rec(_root, "", true);
}


template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::print_tree_rec(RBNode<TKey, TValue>* node, std::string prefix, bool is_last) const {
    if (!node) return;
    std::cout << prefix;

    if (!prefix.empty()) {
        std::cout << (is_last ? "|__" : "|--");
    }


    std::cout << "(" << node->value.first << ", " << node->value.second << ", " << node->color << ")\n";

    std::string new_prefix = prefix + (is_last ? "    " : "|   ");

    if (node->right)
        print_tree_rec(node->right, new_prefix, node->left == nullptr);

    if (node->left)
        print_tree_rec(node->left, new_prefix, true);
}