#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace learning {

template <typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  explicit BinarySearchTree(Compare compare) : compare_(std::move(compare)) {}

  [[nodiscard]] bool insert(const Key& key, const Value& value) {
    return emplace(key, value);
  }

  [[nodiscard]] bool insert(Key&& key, Value&& value) {
    return emplace(std::move(key), std::move(value));
  }

  template <typename K, typename V>
  [[nodiscard]] bool emplace(K&& key, V&& value) {
    return emplace_impl(root_, std::forward<K>(key), std::forward<V>(value));
  }

  [[nodiscard]] bool erase(const Key& key) { return erase_impl(root_, key); }

  [[nodiscard]] Value* find(const Key& key) {
    Node* node = find_node(root_.get(), key);
    return node ? &node->value : nullptr;
  }

  [[nodiscard]] const Value* find(const Key& key) const {
    const Node* node = find_node(root_.get(), key);
    return node ? &node->value : nullptr;
  }

  [[nodiscard]] bool contains(const Key& key) const { return find(key) != nullptr; }

  void clear() {
    root_.reset();
    size_ = 0;
  }

  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

  [[nodiscard]] std::size_t size() const noexcept { return size_; }

  [[nodiscard]] std::vector<Key> inorder_keys() const {
    std::vector<Key> keys;
    keys.reserve(size_);
    inorder([&keys](const Key& key, const Value&) { keys.push_back(key); });
    return keys;
  }

  template <typename Fn>
  void inorder(Fn&& visitor) const {
    auto fn = std::forward<Fn>(visitor);
    inorder_impl(root_.get(), fn);
  }

 private:
  struct Node {
    Key key;
    Value value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    template <typename K, typename V>
    Node(K&& node_key, V&& node_value)
        : key(std::forward<K>(node_key)), value(std::forward<V>(node_value)) {}
  };

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
    node->key = successor->key;
    node->value = successor->value;
    return erase_impl(node->right, successor->key);
  }

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

  Node* min_node(Node* node) const {
    Node* current = node;
    while (current && current->left) {
      current = current->left.get();
    }
    return current;
  }

  template <typename Fn>
  void inorder_impl(const Node* node, Fn& visitor) const {
    if (!node) {
      return;
    }

    inorder_impl(node->left.get(), visitor);
    visitor(node->key, node->value);
    inorder_impl(node->right.get(), visitor);
  }

  std::unique_ptr<Node> root_;
  Compare compare_;
  std::size_t size_ = 0;
};

}  // namespace learning
