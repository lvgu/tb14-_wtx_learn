#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace learning {

// 二叉搜索树（BST）
// 约束：左子树键值 < 当前节点键值 < 右子树键值
// 当前实现不允许重复 key（重复插入返回 false）
template <typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  // 支持自定义比较器（例如降序、复合键比较等）
  explicit BinarySearchTree(Compare compare) : compare_(std::move(compare)) {}

  // 拷贝方式插入
  [[nodiscard]] bool insert(const Key& key, const Value& value) {
    return emplace(key, value);
  }

  // 移动方式插入
  [[nodiscard]] bool insert(Key&& key, Value&& value) {
    return emplace(std::move(key), std::move(value));
  }

  // 完美转发插入，避免不必要拷贝
  template <typename K, typename V>
  [[nodiscard]] bool emplace(K&& key, V&& value) {
    return emplace_impl(root_, std::forward<K>(key), std::forward<V>(value));
  }

  // 删除指定 key，成功返回 true
  [[nodiscard]] bool erase(const Key& key) { return erase_impl(root_, key); }

  // 查找 key，对应值存在则返回指针
  [[nodiscard]] Value* find(const Key& key) {
    Node* node = find_node(root_.get(), key);
    return node ? &node->value : nullptr;
  }

  // const 版本查找
  [[nodiscard]] const Value* find(const Key& key) const {
    const Node* node = find_node(root_.get(), key);
    return node ? &node->value : nullptr;
  }

  // 仅判断 key 是否存在
  [[nodiscard]] bool contains(const Key& key) const { return find(key) != nullptr; }

  // 清空整棵树
  void clear() {
    root_.reset();
    size_ = 0;
  }

  // 状态查询
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

  [[nodiscard]] std::size_t size() const noexcept { return size_; }

  // 返回中序遍历键序列（天然有序）
  [[nodiscard]] std::vector<Key> inorder_keys() const {
    std::vector<Key> keys;
    keys.reserve(size_);
    inorder([&keys](const Key& key, const Value&) { keys.push_back(key); });
    return keys;
  }

  // 通用中序遍历：调用方传入访问函数
  template <typename Fn>
  void inorder(Fn&& visitor) const {
    auto fn = std::forward<Fn>(visitor);
    inorder_impl(root_.get(), fn);
  }

 private:
  // BST 节点结构
  struct Node {
    Key key;
    Value value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    template <typename K, typename V>
    Node(K&& node_key, V&& node_value)
        : key(std::forward<K>(node_key)), value(std::forward<V>(node_value)) {}
  };

  // 递归插入：
  // 1. 空位置直接创建节点
  // 2. 比较后进入左/右子树
  // 3. 相等则视为重复键，返回 false
  template <typename K, typename V>
  bool emplace_impl(std::unique_ptr<Node>& node, K&& key, V&& value) {
    if (!node) {
      node = std::make_unique<Node>(std::forward<K>(key), std::forward<V>(value));
      ++size_;
      return true;
    }

    if (compare_(key, node->key)) {
      return emplace_impl(node->left, std::forward<K>(key), std::forward<V>(value));
    }

    if (compare_(node->key, key)) {
      return emplace_impl(node->right, std::forward<K>(key), std::forward<V>(value));
    }

    return false;
  }

  // 递归删除：
  // 1. 叶子节点直接删
  // 2. 单子树节点用子树顶替
  // 3. 双子树节点用右子树最小节点（中序后继）顶替
  bool erase_impl(std::unique_ptr<Node>& node, const Key& key) {
    if (!node) {
      return false;
    }

    if (compare_(key, node->key)) {
      return erase_impl(node->left, key);
    }

    if (compare_(node->key, key)) {
      return erase_impl(node->right, key);
    }

    if (!node->left && !node->right) {
      node.reset();
      --size_;
      return true;
    }

    if (!node->left) {
      node = std::move(node->right);
      --size_;
      return true;
    }

    if (!node->right) {
      node = std::move(node->left);
      --size_;
      return true;
    }

    Node* successor = min_node(node->right.get());
    // 用后继节点的键值覆盖当前节点，再在右子树删除后继
    node->key = successor->key;
    node->value = successor->value;
    return erase_impl(node->right, successor->key);
  }

  // 递归查找（可修改版本）
  Node* find_node(Node* node, const Key& key) const {
    if (!node) {
      return nullptr;
    }

    if (compare_(key, node->key)) {
      return find_node(node->left.get(), key);
    }

    if (compare_(node->key, key)) {
      return find_node(node->right.get(), key);
    }

    return node;
  }

  // 递归查找（只读版本）
  const Node* find_node(const Node* node, const Key& key) const {
    if (!node) {
      return nullptr;
    }

    if (compare_(key, node->key)) {
      return find_node(node->left.get(), key);
    }

    if (compare_(node->key, key)) {
      return find_node(node->right.get(), key);
    }

    return node;
  }

  // 取子树中的最小节点（一路向左）
  Node* min_node(Node* node) const {
    Node* current = node;
    while (current && current->left) {
      current = current->left.get();
    }
    return current;
  }

  // 中序遍历：左 -> 根 -> 右
  template <typename Fn>
  void inorder_impl(const Node* node, Fn& visitor) const {
    if (!node) {
      return;
    }

    inorder_impl(node->left.get(), visitor);
    visitor(node->key, node->value);
    inorder_impl(node->right.get(), visitor);
  }

  // 根节点指针
  std::unique_ptr<Node> root_;
  // 比较器实例
  Compare compare_;
  // 节点数量缓存，便于 O(1) 返回 size
  std::size_t size_ = 0;
};

}  // namespace learning
