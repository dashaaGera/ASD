#include "../lib_hash_table_chain/hash_table_c.h"
#include <gtest/gtest.h>

TEST(TestHashTableChain, is_empty_works_correctly) {
    HashTableChain<std::string> table(10);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert("one", "1");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);

    table.insert("two", "2");
    table.insert("three", "3");
    EXPECT_EQ(table.size(), 3);
    EXPECT_FALSE(table.is_empty());

    table.erase("one");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.is_empty());

    table.erase("two");
    table.erase("three");
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}


TEST(TestHashTableChain, consist_works_correctly) {
    HashTableChain<int> table(20);

    EXPECT_FALSE(table.consist("key1"));
    EXPECT_FALSE(table.consist("key2"));

    table.insert("key1", 100);
    table.insert("key2", 200);
    table.insert("key3", 300);

    EXPECT_TRUE(table.consist("key1"));
    EXPECT_TRUE(table.consist("key2"));
    EXPECT_TRUE(table.consist("key3"));
    EXPECT_FALSE(table.consist("key4"));
    EXPECT_FALSE(table.consist("KEY1")); 

    EXPECT_EQ(table.size(), 3);
    EXPECT_FALSE(table.is_empty());
}


TEST(TestHashTableChain, find_works_correctly) {
    HashTableChain<std::string> table(15);

    table.insert("name", "John");
    table.insert("city", "Moscow");
    table.insert("age", "25");

    EXPECT_EQ(table.find("name"), "John");
    EXPECT_EQ(table.find("city"), "Moscow");
    EXPECT_EQ(table.find("age"), "25");

    EXPECT_THROW(table.find("country"), std::logic_error);
    EXPECT_THROW(table.find("nonexistent"), std::logic_error);

}


TEST(TestHashTableChain, erase_works_correctly) {
    HashTableChain<char> table(10);

    table.insert("a", 'A');
    table.insert("b", 'B');
    table.insert("c", 'C');
    table.insert("d", 'D');

    EXPECT_EQ(table.size(), 4);
    table.erase("b");
    EXPECT_EQ(table.size(), 3);
    EXPECT_FALSE(table.consist("b"));
    EXPECT_TRUE(table.consist("a"));
    EXPECT_TRUE(table.consist("c"));
    EXPECT_TRUE(table.consist("d"));

    table.erase("d");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("b"));
    EXPECT_FALSE(table.consist("d"));

    EXPECT_EQ(table.find("a"), 'A');
    EXPECT_EQ(table.find("c"), 'C');

    EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
}

TEST(TestHashTableChain, collisions_handled_correctly) {
    HashTableChain<int> table(5);

    table.insert("abc", 1);  
    table.insert("cba", 2);   
    table.insert("bac", 3);  

    EXPECT_EQ(table.size(), 3);

    EXPECT_TRUE(table.consist("abc"));
    EXPECT_TRUE(table.consist("cba"));
    EXPECT_TRUE(table.consist("bac"));

    EXPECT_EQ(table.find("abc"), 1);
    EXPECT_EQ(table.find("cba"), 2);
    EXPECT_EQ(table.find("bac"), 3);

    table.erase("cba");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("cba"));
    EXPECT_TRUE(table.consist("abc"));
    EXPECT_TRUE(table.consist("bac"));

    EXPECT_EQ(table.find("abc"), 1);
    EXPECT_EQ(table.find("bac"), 3);
}

TEST(TestHashTableChain, exceptions_on_empty_table) {
    HashTableChain<double> table(10);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_THROW(table.find("anything"), std::logic_error);
    EXPECT_THROW(table.erase("anything"), std::logic_error);
    EXPECT_FALSE(table.consist("anything"));
    table.insert("test", 3.14);
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
}

TEST(TestHashTableChain, func_print_work_correctly) {
    HashTableChain<std::string> table(100);

    table.insert("five", "5");
    table.insert("two", "2");
    table.insert("eight", "8");
    table.insert("one", "1");

    std::stringstream output;
    table.print(output);
    std::string result = output.str();

    std::string expected = "Bucket 22: [one: 1] \nBucket 26: [five: 5] \nBucket 29: [eight: 8] \nBucket 46: [two: 2] \n";
    EXPECT_EQ(result, expected);
}