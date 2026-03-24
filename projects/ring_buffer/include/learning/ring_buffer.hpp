#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace learning {

// 固定容量的环形缓冲区（FIFO）
// 特点：
// 1. 入队/出队均为 O(1)
// 2. 满时 push/emplace 返回 false，不覆盖旧数据
template <typename T>
class RingBuffer {
 public:
  // 构造时指定容量，容量必须大于 0
  explicit RingBuffer(std::size_t capacity)
      : storage_(capacity), capacity_(capacity) {
    if (capacity_ == 0) {
      throw std::invalid_argument("RingBuffer capacity must be greater than 0");
    }
  }

  // 拷贝方式入队
  [[nodiscard]] bool push(const T& value) { return emplace(value); }

  // 移动方式入队
  [[nodiscard]] bool push(T&& value) { return emplace(std::move(value)); }

  // 原地构造入队，缓冲区满则失败
  template <typename... Args>
  [[nodiscard]] bool emplace(Args&&... args) {
    if (full()) {
      return false;
    }

    // tail_ 指向“下一次写入位置”
    storage_[tail_].emplace(std::forward<Args>(args)...);
    tail_ = next_index(tail_);
    ++size_;
    return true;
  }

  // 出队但不返回值，仅表示是否成功
  [[nodiscard]] bool pop() {
    if (empty()) {
      return false;
    }

    // 清空当前头元素，再移动头指针
    storage_[head_].reset();
    head_ = next_index(head_);
    --size_;
    return true;
  }

  // 出队并返回值；空队列返回 nullopt
  [[nodiscard]] std::optional<T> pop_value() {
    if (empty()) {
      return std::nullopt;
    }

    // 通过移动语义减少拷贝开销
    std::optional<T> value = std::move(storage_[head_]);
    storage_[head_].reset();
    head_ = next_index(head_);
    --size_;
    return value;
  }

  // 返回队头指针；空队列返回 nullptr
  [[nodiscard]] T* front() {
    if (empty()) {
      return nullptr;
    }
    return &storage_[head_].value();
  }

  // const 版本队头访问
  [[nodiscard]] const T* front() const {
    if (empty()) {
      return nullptr;
    }
    return &storage_[head_].value();
  }

  // 返回队尾元素指针；空队列返回 nullptr
  [[nodiscard]] T* back() {
    if (empty()) {
      return nullptr;
    }

    // tail_ 指向下一写入位，因此真实队尾是其前一个位置
    const std::size_t index = previous_index(tail_);
    return &storage_[index].value();
  }

  // const 版本队尾访问
  [[nodiscard]] const T* back() const {
    if (empty()) {
      return nullptr;
    }

    const std::size_t index = previous_index(tail_);
    return &storage_[index].value();
  }

  // 清空所有元素
  void clear() {
    while (pop()) {
    }
  }

  // 状态查询接口
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

  [[nodiscard]] bool full() const noexcept { return size_ == capacity_; }

  [[nodiscard]] std::size_t size() const noexcept { return size_; }

  [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }

 private:
  // 下一个索引（循环回绕）
  [[nodiscard]] std::size_t next_index(std::size_t index) const noexcept {
    return (index + 1) % capacity_;
  }

  // 上一个索引（循环回绕）
  [[nodiscard]] std::size_t previous_index(std::size_t index) const noexcept {
    return (index + capacity_ - 1) % capacity_;
  }

  // 使用 optional 便于“已占用/空槽位”状态管理
  std::vector<std::optional<T>> storage_;
  // 固定容量，不随运行时变化
  std::size_t capacity_;
  // head_ 指向当前队头，tail_ 指向下一次写入位置
  std::size_t head_ = 0;
  std::size_t tail_ = 0;
  // 当前有效元素个数
  std::size_t size_ = 0;
};

}  // namespace learning
