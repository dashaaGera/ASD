#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

TEST(TestDSU, can_create_with_init_constructor) {
    ASSERT_NO_THROW(DSU d(8));
}

TEST(TestDSU, can_create_with_init_constructor_correctly) {
    DSU d(7);
    EXPECT_EQ(d.size(), 7);
    for (int i=0;i < d.size();i++) {
        EXPECT_EQ(d.parent()[i], i);
        EXPECT_EQ(d.rank()[i], 0);
    }

}

TEST(TestDSU, rank_changes_after_unite) {
    DSU d(6);

    d.unite(0, 1);
    EXPECT_EQ(d.rank()[d.find(0)], 1);

    d.unite(2, 3);
    EXPECT_EQ(d.rank()[d.find(2)], 1);

    d.unite(0, 2);
    EXPECT_EQ(d.rank()[d.find(0)], 2);

    d.unite(4, 5);
    EXPECT_EQ(d.rank()[d.find(4)], 1);
    d.unite(0, 4);
    EXPECT_EQ(d.rank()[d.find(0)], 2);
}

TEST(TestDSU, unite_different_sets_work_correctly) {
    DSU d(5);
    d.unite(0, 1);
    d.unite(2, 3);

    EXPECT_EQ(d.find(0), d.find(1));  
    EXPECT_EQ(d.find(2), d.find(3));  
    EXPECT_NE(d.find(0), d.find(2));  
}

TEST(TestDSU, unite_work_correctly) {
    DSU d(6);
    //0 1 2 3
    d.unite(1, 0);
    EXPECT_EQ(d.parent()[0], 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(1, 1);
    EXPECT_EQ(d.parent()[0], 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(2, 1);
    EXPECT_EQ(d.parent()[0], 1);
    EXPECT_EQ(d.rank()[1], 1);
    d.unite(3, 2);
    EXPECT_EQ(d.parent()[0], 1);
    EXPECT_EQ(d.rank()[1], 1);

    int root = d.find(3);  

    EXPECT_EQ(d.parent()[3], root);
    EXPECT_EQ(d.parent()[2], root);
    EXPECT_EQ(d.parent()[1], root);
}