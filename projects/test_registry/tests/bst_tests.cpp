#include <string>
#include <vector>

#include "learning/bst.hpp"
#include "learning/test_registry.hpp"

LEARNING_TEST(bst_insert_find_and_contains) {
  learning::BinarySearchTree<int, std::string> tree;

  LEARNING_EXPECT_TRUE(tree.insert(7, "root"));
  LEARNING_EXPECT_TRUE(tree.insert(3, "left"));
  LEARNING_EXPECT_TRUE(tree.insert(9, "right"));
  LEARNING_EXPECT_TRUE(!tree.insert(7, "duplicate"));

  LEARNING_EXPECT_TRUE(tree.contains(3));
  LEARNING_EXPECT_TRUE(tree.contains(9));
  LEARNING_EXPECT_TRUE(!tree.contains(100));
  LEARNING_EXPECT_EQ(tree.size(), static_cast<std::size_t>(3));

  const auto* value = tree.find(9);
  LEARNING_EXPECT_TRUE(value != nullptr);
  LEARNING_EXPECT_EQ(*value, std::string("right"));
}

LEARNING_TEST(bst_erase_and_inorder_sorted) {
  learning::BinarySearchTree<int, int> tree;
  LEARNING_EXPECT_TRUE(tree.insert(8, 80));
  LEARNING_EXPECT_TRUE(tree.insert(3, 30));
  LEARNING_EXPECT_TRUE(tree.insert(10, 100));
  LEARNING_EXPECT_TRUE(tree.insert(1, 10));
  LEARNING_EXPECT_TRUE(tree.insert(6, 60));
  LEARNING_EXPECT_TRUE(tree.insert(14, 140));
  LEARNING_EXPECT_TRUE(tree.insert(4, 40));
  LEARNING_EXPECT_TRUE(tree.insert(7, 70));
  LEARNING_EXPECT_TRUE(tree.insert(13, 130));

  LEARNING_EXPECT_TRUE(tree.erase(3));
  LEARNING_EXPECT_TRUE(!tree.contains(3));
  LEARNING_EXPECT_EQ(tree.size(), static_cast<std::size_t>(8));

  const std::vector<int> expected{1, 4, 6, 7, 8, 10, 13, 14};
  LEARNING_EXPECT_EQ(tree.inorder_keys(), expected);
}
