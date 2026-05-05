#include "../lib_rb_tree/rb_tree.h"
#include <gtest/gtest.h>
#include <string>
TEST(TestRBNode, can_create_with_init_constructor_correctly) {
    RBNode<int, int> n1;
    EXPECT_EQ(n1.value.first, 0);
    EXPECT_EQ(n1.value.second, 0);
    EXPECT_EQ(n1.left, nullptr);
    EXPECT_EQ(n1.right, nullptr);
    EXPECT_EQ(n1.parent, nullptr);
    EXPECT_EQ(n1.color, RBColor::RED);

    RBNode<int, int> n2(std::pair<int, int>(5, 10));
    EXPECT_EQ(n2.value.first, 5);
    EXPECT_EQ(n2.value.second, 10);
    EXPECT_EQ(n2.left, nullptr);
    EXPECT_EQ(n2.right, nullptr);
    EXPECT_EQ(n2.parent, nullptr);
    EXPECT_EQ(n2.color, RBColor::RED);

    RBNode<int, int> child1(std::pair<int, int>(1, 2));
    RBNode<int, int> child2(std::pair<int, int>(3, 4));
    RBNode<int, int> parent(std::pair<int, int>(7, 4));

    RBNode<int, int> n3(std::pair<int, int>(5, 6), &parent);
    EXPECT_EQ(n3.value.first, 5);
    EXPECT_EQ(n3.value.second, 6);
    EXPECT_EQ(n3.parent, &parent);
    EXPECT_EQ(n3.right, nullptr);
    EXPECT_EQ(n3.left, nullptr);
    EXPECT_EQ(n3.color, RBColor::RED);

    RBNode<int, int> n4(std::pair<int, int>(7, 8), &parent, &child2);
    EXPECT_EQ(n4.value.first, 7);
    EXPECT_EQ(n4.value.second, 8);
    EXPECT_EQ(n4.parent, &parent);
    EXPECT_EQ(n4.left, &child2);
    EXPECT_EQ(n4.right, nullptr);
    EXPECT_EQ(n4.color, RBColor::RED);


    RBNode<int, int> n5(std::pair<int, int>(7, 8), &parent, &child1, &child2, RBColor::BLACK);
    EXPECT_EQ(n5.value.first, 7);
    EXPECT_EQ(n5.value.second, 8);
    EXPECT_EQ(n5.left, &child1);
    EXPECT_EQ(n5.right, &child2);
    EXPECT_EQ(n5.parent, &parent);
    EXPECT_EQ(n5.color, RBColor::BLACK);
}
TEST(TestRBTree, can_create_with_init_constructor_correctly) {
    RBTree<int, int> t1;
    EXPECT_EQ(t1.root(), nullptr);
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
}

TEST(TestRBTree, find_work_correctly) {
    RBTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.insert(2, "two");
    EXPECT_EQ(t1.find(1), "one");
    EXPECT_EQ(t1.find(2), "two");
    ASSERT_THROW(t1.find(6), std::logic_error);
}

TEST(TestRBTree, can_insert_correctly_case_recolor) {
    RBTree<int, int> t1;
    t1.insert(1, 1);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    t1.insert(3, 3);
    t1.insert(7, 7);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);
    t1.insert(8, 8);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->right->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->right->right->color, RBColor::RED);

}


TEST(TestRBTree, can_insert_correctly_case_rotate_ll) {
    //   10(B)        5(B)
    //   /     ->     / \
    //  5(R)        3(R) 10(R)
    // /
    //3(R)

    RBTree<int, int> t1;
    t1.insert(10, 10);
    t1.insert(5, 5);
    t1.insert(3, 3);

    EXPECT_EQ(t1.root()->value.first, 5);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->value.first, 3);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->value.first, 10);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);

    EXPECT_EQ(t1.to_string(), "5 3 10 ");
    EXPECT_EQ(t1.to_string_sorted(), "3 5 10 ");
}

TEST(TestRBTree, can_insert_correctly_case_rotate_rr) {
    // 10(B)          15(B)
    //   \       ->   / \
    //   15(R)      10(R) 20(R)
    //     \
    //     20(R)

    RBTree<int, int> t1;
    t1.insert(10, 10);
    t1.insert(15, 15);
    t1.insert(20, 20);

    EXPECT_EQ(t1.root()->value.first, 15);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->value.first, 10);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->value.first, 20);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);
    EXPECT_EQ(t1.to_string(), "15 10 20 ");
    EXPECT_EQ(t1.to_string_sorted(), "10 15 20 ");
}

TEST(TestRBTree, can_insert_correctly_case_rotate_lr) {
    //    10(B)        7(B)
    //    /      ->    / \
    //   5(R)        5(R) 10(R)
    //    \
    //     7(R)

    RBTree<int, int> t1;
    t1.insert(10, 10);
    t1.insert(5, 5);
    t1.insert(7, 7);
    EXPECT_EQ(t1.root()->value.first, 7);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->value.first, 5);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->value.first, 10);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);
    EXPECT_EQ(t1.to_string(), "7 5 10 ");
    EXPECT_EQ(t1.to_string_sorted(), "5 7 10 ");
}

TEST(TestRBTree, can_insert_correctly_case_rotate_rl) {
    // 10(B)          13(B)
    //   \      ->    / \
    //   15(R)      10(R) 15(R)
    //   /
    // 13(R)

    RBTree<int, int> t1;
    t1.insert(10, 10);
    t1.insert(15, 15);
    t1.insert(13, 13);

    EXPECT_EQ(t1.root()->value.first, 13);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->value.first, 10);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->value.first, 15);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);
    EXPECT_EQ(t1.to_string(), "13 10 15 ");
    EXPECT_EQ(t1.to_string_sorted(), "10 13 15 ");
}

TEST(TestRBTree, can_insert_correctly_all_cases) {
    RBTree<int, int> t1;

    t1.insert(10, 10);
    EXPECT_EQ(t1.root()->value.first, 10);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.size(), 1);

    t1.insert(5, 5);
    EXPECT_EQ(t1.root()->left->value.first, 5);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.size(), 2);

    // LL 
    t1.insert(3, 3);
    EXPECT_EQ(t1.root()->value.first, 5);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->value.first, 3);
    EXPECT_EQ(t1.root()->left->color, RBColor::RED);
    EXPECT_EQ(t1.root()->right->value.first, 10);
    EXPECT_EQ(t1.root()->right->color, RBColor::RED);
    EXPECT_EQ(t1.size(), 3);

    //recolor
    t1.insert(7, 7);
    t1.insert(8, 8);
    EXPECT_EQ(t1.size(), 5);
    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->right->color, RBColor::BLACK);
    EXPECT_EQ(t1.root()->right->right->color, RBColor::RED);


    EXPECT_EQ(t1.root()->color, RBColor::BLACK);
    EXPECT_EQ(t1.to_string(), "5 3 8 7 10 ");
    EXPECT_EQ(t1.to_string_sorted(), "3 5 7 8 10 ");

}

TEST(TestRBTree, can_erase_correctly_case_delete_red) {
    RBTree<int, int> t;
    t.insert(10, 1);
    t.insert(5, 1); // red
    t.erase(5);
    EXPECT_EQ(t.to_string(), "10 ");
    EXPECT_EQ(t.to_string_sorted(), "10 ");
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
}

TEST(TestRBTree, can_erase_correctly_case_replacer_red) {
    RBTree<int, int> t;
    t.insert(50, 1);
    t.insert(25, 1);
    t.insert(75, 1);
    t.insert(10, 1);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->left->color, RBColor::RED);
    t.erase(25);
    EXPECT_EQ(t.to_string(), "50 10 75 ");
    EXPECT_EQ(t.to_string_sorted(), "10 50 75 ");
    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->color, RBColor::BLACK);
}

TEST(TestRBTree, can_erase_correctly_case_s_black_cs_red) {
    RBTree<int, int> t;

    t.insert(50, 1);
    t.insert(35, 1);
    t.insert(70, 1);
    t.insert(20, 1);
    t.insert(40, 1);
    t.insert(60, 1);
    t.insert(90, 1);
    t.insert(100, 1);
    t.insert(110, 1);
    t.insert(120, 1);
    t.erase(120);
    t.erase(90);
    t.insert(120, 1);
    t.erase(100);
    t.erase(110);
    t.insert(10,1);
    t.insert(55, 1);
    t.insert(65, 1);
    t.insert(90, 1);
    t.insert(130, 1);
    t.insert(150, 1);
    t.erase(35);
    t.erase( 10);
    t.erase(20);
    t.print_tree();
    EXPECT_EQ(t.to_string(), "70 50 120 40 60 90 130 55 65 150 ");
    EXPECT_EQ(t.size(), 10);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->color, RBColor::BLACK);
    
}

TEST(TestRBTree, can_erase_correctly_case_s_black_children_s_black) {
    RBTree<int, int> t;

    t.insert(50, 1);
    t.insert(35, 1);
    t.insert(70, 1);
    t.insert(20, 1);
    t.insert(40, 1);
    t.insert(60, 1);
    t.insert(90, 1);
    t.insert(100, 1);
    t.insert(110, 1);
    t.insert(120, 1);
    t.erase(120);
    t.erase(90);
    t.insert(120, 1);
    t.erase(100);
    t.erase(110);
    t.insert(10, 1);
    t.insert(55, 1);
    t.insert(65, 1);
    t.insert(90, 1);
    t.insert(130, 1);
    t.insert(150, 1);
    t.erase(35);
    t.erase(10);
    t.erase(20);
    t.erase(150);
    t.erase(130);
    t.erase(120);
    t.print_tree();
    EXPECT_EQ(t.to_string(), "70 50 90 40 60 55 65 ");
    EXPECT_EQ(t.size(), 7);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->color, RBColor::RED);
    EXPECT_EQ(t.root()->left->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->color, RBColor::BLACK);

}

TEST(TestRBTree, can_erase_correctly_case_s_red) {
    RBTree<int, int> t;

    t.insert(50, 1);
    t.insert(35, 1);
    t.insert(70, 1);
    t.insert(20, 1);
    t.insert(40, 1);
    t.insert(60, 1);
    t.insert(90, 1);
    t.insert(100, 1);
    t.insert(110, 1);
    t.insert(120, 1);
    t.erase(120);
    t.erase(90);
    t.insert(120, 1);
    t.erase(100);
    t.erase(110);
    t.insert(10, 1);
    t.insert(55, 1);
    t.insert(65, 1);
    t.insert(90, 1);
    t.insert(130, 1);
    t.insert(150, 1);
    t.erase(35);
    t.erase(10);
    t.erase(20);
    t.erase(150);
    t.erase(130);
    t.erase(120);
    t.erase(90);
    t.print_tree();
    EXPECT_EQ(t.to_string(), "50 40 60 55 70 65 ");
    EXPECT_EQ(t.size(), 6);
    EXPECT_EQ(t.root()->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->left->color, RBColor::BLACK);
    EXPECT_EQ(t.root()->right->color, RBColor::RED);

}

