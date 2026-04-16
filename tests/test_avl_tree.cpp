#include "../lib_avl_tree/avl_tree.h"
#include <gtest/gtest.h>
#include <string>
TEST(TestAVLNode, can_create_with_init_constructor_correctly) {
    AVLNode<int, int> n1;
    EXPECT_EQ(n1.value.first, 0);
    EXPECT_EQ(n1.value.second, 0);
    EXPECT_EQ(n1.left, nullptr);
    EXPECT_EQ(n1.right, nullptr);
    EXPECT_EQ(n1.parent, nullptr);
    EXPECT_EQ(n1.height, 1);

    AVLNode<int, int> n2(std::pair<int, int>(5, 10));
    EXPECT_EQ(n2.value.first, 5);
    EXPECT_EQ(n2.value.second, 10);
    EXPECT_EQ(n2.left, nullptr);
    EXPECT_EQ(n2.right, nullptr);
    EXPECT_EQ(n2.parent, nullptr);
    EXPECT_EQ(n2.height, 1);

    AVLNode<int, int> child1(std::pair<int, int>(1, 2));
    AVLNode<int, int> child2(std::pair<int, int>(3, 4));
    AVLNode<int, int> parent(std::pair<int, int>(7, 4));

    AVLNode<int, int> n3(std::pair<int, int>(5, 6), &parent);
    EXPECT_EQ(n3.value.first, 5);
    EXPECT_EQ(n3.value.second, 6);
    EXPECT_EQ(n3.parent, &parent);
    EXPECT_EQ(n3.right, nullptr);
    EXPECT_EQ(n3.left, nullptr);
    EXPECT_EQ(n3.height, 1);

    AVLNode<int, int> n4(std::pair<int, int>(7, 8), &parent, &child2);
    EXPECT_EQ(n4.value.first, 7);
    EXPECT_EQ(n4.value.second, 8);
    EXPECT_EQ(n4.parent, &parent);
    EXPECT_EQ(n4.left, &child2);
    EXPECT_EQ(n4.right, nullptr);
    EXPECT_EQ(n4.height, 1);


    AVLNode<int, int> n5(std::pair<int, int>(7, 8), &parent, &child1, &child2,8);
    EXPECT_EQ(n5.value.first, 7);
    EXPECT_EQ(n5.value.second, 8);
    EXPECT_EQ(n5.left, &child1);
    EXPECT_EQ(n5.right, &child2);
    EXPECT_EQ(n5.parent, &parent);
    EXPECT_EQ(n5.height, 8);
}
TEST(TestAVLTree, can_create_with_init_constructor_correctly) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.root(), nullptr);
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
}


TEST(TestAVLTree, insert_work_correctly_case_LL) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(4, 4);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(3, 3);
    t1.insert(2, 2);
    EXPECT_EQ(t1.to_string(), "5 3 6 2 4 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 3 4 5 6 ");
    EXPECT_EQ(t1.root()->height, 3);
    EXPECT_EQ(t1.root()->left->height, 2);
    EXPECT_EQ(t1.root()->right->height, 1);
    EXPECT_EQ(t1.size(), 5);

}



TEST(TestAVLTree, insert_work_correctly_case_RR) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(4, 4);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(7, 7);
    t1.insert(8, 8);
    EXPECT_EQ(t1.to_string(), "5 4 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "4 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly_case_LR) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(8, 8);
    t1.insert(6, 6);
    t1.insert(7, 7);
    EXPECT_EQ(t1.to_string(), "5 2 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly_case_RL) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    t1.insert(2, 2);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 2);
    t1.insert(6, 6);
    t1.insert(8, 8);
    t1.insert(7, 7);
    EXPECT_EQ(t1.to_string(), "5 2 7 6 8 ");
    EXPECT_EQ(t1.to_string_sorted(), "2 5 6 7 8 ");
    EXPECT_EQ(t1.size(), 5);
}

TEST(TestAVLTree, insert_work_correctly) {
    AVLTree<int, int> t1;
    EXPECT_EQ(t1.is_empty(), true);
    EXPECT_EQ(t1.size(), 0);
    t1.insert(5, 5);
    t1.insert(5, 5);
    EXPECT_EQ(t1.is_empty(), false);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.to_string(), "5 ");

}
TEST(TestAVLTree, find_work_correctly) {
    AVLTree<int, std::string> t1;
    EXPECT_EQ(t1.is_empty(), true);
    t1.insert(1, "one");
    t1.insert(2, "two");
    EXPECT_EQ(t1.find(1), "one");
    EXPECT_EQ(t1.find(2), "two");
    ASSERT_THROW(t1.find(6), std::logic_error);
}

TEST(TestAVLTree, erase_work_correctly_case_no_balance) {
    AVLTree<int, std::string> tree;
    EXPECT_EQ(tree.is_empty(), true);
    EXPECT_EQ(tree.size(), 0);
    tree.insert(50, "A");
    tree.insert(30, "B");
    tree.insert(70, "C");
    tree.insert(40, "D");
    tree.insert(60, "E");
    tree.insert(80, "F");
    EXPECT_EQ(tree.is_empty(), false);
    EXPECT_EQ(tree.size(), 6);
    EXPECT_EQ(tree.to_string(), "50 30 70 40 60 80 ");
    tree.erase(30);
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.to_string(), "50 40 70 60 80 ");
    EXPECT_EQ(tree.to_string_sorted(), "40 50 60 70 80 ");

}

TEST(TestAVLTree, erase_work_correctly_case_LL) {
    AVLTree<int, std::string> tree;
    EXPECT_EQ(tree.is_empty(), true);
    EXPECT_EQ(tree.size(), 0);
    tree.insert(40, "A");
    tree.insert(30, "B");
    tree.insert(50, "C");
    tree.insert(20, "D");
    tree.insert(35, "E");
    EXPECT_EQ(tree.is_empty(), false);
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.to_string(), "40 30 50 20 35 ");
    tree.erase(50);
    EXPECT_EQ(tree.size(), 4);
    EXPECT_EQ(tree.to_string(), "30 20 40 35 ");
    EXPECT_EQ(tree.to_string_sorted(), "20 30 35 40 ");

}

TEST(TestAVLTree, erase_work_correctly_case_RR) {
    AVLTree<int, std::string> tree;
    EXPECT_EQ(tree.is_empty(), true);
    EXPECT_EQ(tree.size(), 0);
    tree.insert(40, "A");
    tree.insert(30, "B");
    tree.insert(60, "C");
    tree.insert(50, "D");
    tree.insert(70, "E");
    EXPECT_EQ(tree.is_empty(), false);
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.to_string(), "40 30 60 50 70 ");
    tree.erase(30);
    EXPECT_EQ(tree.size(), 4);
    EXPECT_EQ(tree.to_string(), "60 40 70 50 ");
    EXPECT_EQ(tree.to_string_sorted(), "40 50 60 70 ");

}

TEST(TestAVLTree, erase_work_corretly_case_LR)
{
    AVLTree<int, int> t;
    t.insert(50, 1);
    t.insert(30, 1);
    t.insert(70, 1);
    t.insert(40, 1);
    EXPECT_EQ(t.size(), 4);
    EXPECT_EQ(t.to_string(), "50 30 70 40 ");
    t.erase(70);  
    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t.to_string(), "40 30 50 ");
    EXPECT_EQ(t.to_string_sorted(), "30 40 50 ");
}

TEST(TestAVLTree, erase_work_correctly_case_RL)
{
    AVLTree<int, int> t;
    t.insert(50, 1);
    t.insert(30, 1);
    t.insert(70, 1);
    t.insert(60, 1);

    EXPECT_EQ(t.to_string(), "50 30 70 60 ");
    EXPECT_EQ(t.size(), 4);
    t.erase(30);
    EXPECT_EQ(t.size(), 3);
    EXPECT_EQ(t.to_string(), "60 50 70 ");
    EXPECT_EQ(t.to_string_sorted(), "50 60 70 ");
}

TEST(TestAVLTree, erase_work_correctly) {
    AVLTree<int, int> t;
    t.insert(40, 1);
    t.insert(20, 1);
    t.insert(60, 1);
    t.insert(10, 1);
    t.insert(30, 1);
    t.insert(50, 1);
    t.insert(70, 1);
    t.insert(25, 1);

    EXPECT_EQ(t.to_string(), "40 20 60 10 30 50 70 25 ");
    EXPECT_EQ(t.size(), 8);
    t.erase(70);
    EXPECT_EQ(t.to_string(), "40 20 60 10 30 50 25 ");
    EXPECT_EQ(t.size(), 7);

    t.erase(10);
    EXPECT_EQ(t.to_string(), "40 25 60 20 30 50 ");
    EXPECT_EQ(t.size(), 6);

    t.erase(60);
    EXPECT_EQ(t.to_string(), "40 25 50 20 30 ");
    EXPECT_EQ(t.size(), 5);

    t.erase(20);
    EXPECT_EQ(t.to_string(), "40 25 50 30 ");
    EXPECT_EQ(t.size(), 4);

    EXPECT_EQ(t.to_string_sorted(), "25 30 40 50 ");
}

TEST(AVLTree, DeleteCascadeRotations)
{
    AVLTree<int,int> tree;

    tree.insert(60,1);
    tree.insert(40,1);
    tree.insert(80,1);
    tree.insert(30,1);
    tree.insert(50,1);
    tree.insert(70,10);
    tree.insert(90,1);
    tree.insert(20,1);
    tree.insert(35,1);
    tree.insert(45,1);
    tree.insert(55,1);
    tree.insert(65,1);
    tree.insert(75,1);

    EXPECT_EQ(
        tree.to_string(),
        "60 40 80 30 50 70 90 20 35 45 55 65 75 "
    );


    tree.erase(90);
    EXPECT_EQ(
        tree.to_string(),
        "60 40 70 30 50 65 80 20 35 45 55 75 "
    );
}