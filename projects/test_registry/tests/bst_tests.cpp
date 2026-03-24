#include <string>
#include <vector>

#include "learning/bst.hpp"
#include "learning/test_registry.hpp"

// 验证插入、查找、contains 与重复键行为
LEARNING_TEST(bst_insert_find_and_contains) {
  learning::BinarySearchTree<int, std::string> tree;

  // 重复键插入应失败
  LEARNING_EXPECT_TRUE(tree.insert(7, "root"));
  LEARNING_EXPECT_TRUE(tree.insert(3, "left"));
  LEARNING_EXPECT_TRUE(tree.insert(9, "right"));
  LEARNING_EXPECT_TRUE(!tree.insert(7, "duplicate"));

  // 查找和存在性校验
  LEARNING_EXPECT_TRUE(tree.contains(3));
  LEARNING_EXPECT_TRUE(tree.contains(9));
  LEARNING_EXPECT_TRUE(!tree.contains(100));
  LEARNING_EXPECT_EQ(tree.size(), static_cast<std::size_t>(3));

  // 读取命中节点的 value
  const auto* value = tree.find(9);
  LEARNING_EXPECT_TRUE(value != nullptr);
  LEARNING_EXPECT_EQ(*value, std::string("right"));
}

// 验证删除（含双子树节点）与中序有序性
LEARNING_TEST(bst_erase_and_inorder_sorted) {
  learning::BinarySearchTree<int, int> tree;
  // 构造一棵较完整的树
  LEARNING_EXPECT_TRUE(tree.insert(8, 80));
  LEARNING_EXPECT_TRUE(tree.insert(3, 30));
  LEARNING_EXPECT_TRUE(tree.insert(10, 100));
  LEARNING_EXPECT_TRUE(tree.insert(1, 10));
  LEARNING_EXPECT_TRUE(tree.insert(6, 60));
  LEARNING_EXPECT_TRUE(tree.insert(14, 140));
  LEARNING_EXPECT_TRUE(tree.insert(4, 40));
  LEARNING_EXPECT_TRUE(tree.insert(7, 70));
  LEARNING_EXPECT_TRUE(tree.insert(13, 130));

  // 删除 key=3（存在左右子树）
  LEARNING_EXPECT_TRUE(tree.erase(3));
  LEARNING_EXPECT_TRUE(!tree.contains(3));
  LEARNING_EXPECT_EQ(tree.size(), static_cast<std::size_t>(8));

  // 中序遍历结果必须是升序键序列
  const std::vector<int> expected{1, 4, 6, 7, 8, 10, 13, 14};
  LEARNING_EXPECT_EQ(tree.inorder_keys(), expected);
}
