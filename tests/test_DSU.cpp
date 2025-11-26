#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

TEST(TestDSU, constructor_no_throws_exceptions) {
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
    EXPECT_EQ(d.rank()[0], 1);

    d.unite(1, 1);
    EXPECT_EQ(d.rank()[1], 0);

    d.unite(2, 3);
    EXPECT_EQ(d.rank()[2], 1);

    d.unite(0, 2);
    EXPECT_EQ(d.rank()[0], 2);

    d.unite(4, 5);
    EXPECT_EQ(d.rank()[4], 1);
    d.unite(0, 4);
    EXPECT_EQ(d.rank()[0], 2);
}

TEST(TestDSU, unite_different_sets_work_correctly) {
    DSU d(5);
    d.unite(0, 1);
    d.unite(2, 3);

    EXPECT_EQ(d.find(0), d.find(1));  
    EXPECT_EQ(d.find(2), d.find(3));  
    EXPECT_NE(d.find(0), d.find(2));  
}

TEST(TestDSU, find_work_correctly) {
    DSU d(8);
    d.unite(1, 0);
    EXPECT_EQ(d.find(0), 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(2, 1);
    EXPECT_EQ(d.find(2), 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(3, 2);
    EXPECT_EQ(d.find(3), 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(0, 5);
    EXPECT_EQ(d.find(5), 1);
    EXPECT_EQ(d.rank()[1], 1);

    d.unite(7, 6);
    EXPECT_EQ(d.find(6), 7);
    EXPECT_EQ(d.rank()[7], 1);

    d.unite(7, 2);
    EXPECT_EQ(d.find(2), 7);
    EXPECT_EQ(d.rank()[7], 2);
    EXPECT_EQ(d.find(3), 7);

}

TEST(TestDSU, all_functions__work_correctly) {
    DSU d(7);
    d.unite(1, 2);
    d.unite(3, 4);
    d.unite(5, 6);
    d.unite(4, 6);
    d.unite(2, 6);
    EXPECT_EQ(d.find(4), 3);
    EXPECT_EQ(d.find(5), 3);
    EXPECT_EQ(d.find(6), 3);

    EXPECT_EQ(d.find(3), 1);
    EXPECT_EQ(d.find(2), 1);
  
}