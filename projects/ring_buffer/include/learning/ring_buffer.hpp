#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace learning {

template <typename T>
class RingBuffer {
 public:
  explicit RingBuffer(std::size_t capacity)
      : storage_(capacity), capacity_(capacity) {
    if (capacity_ == 0) {
      throw std::invalid_argument("RingBuffer capacity must be greater than 0");
    }
  }

  [[nodiscard]] bool push(const T& value) { return emplace(value); }

  [[nodiscard]] bool push(T&& value) { return emplace(std::move(value)); }

  template <typename... Args>
  [[nodiscard]] bool emplace(Args&&... args) {
    if (full()) {
      return false;
    }

    storage_[tail_].emplace(std::forward<Args>(args)...);
    tail_ = next_index(tail_);
    ++size_;
    return true;
  }

  [[nodiscard]] bool pop() {
    if (empty()) {
      return false;
    }

    storage_[head_].reset();
    head_ = next_index(head_);
    --size_;
    return true;
  }

  [[nodiscard]] std::optional<T> pop_value() {
    if (empty()) {
      return std::nullopt;
    }

    std::optional<T> value = std::move(storage_[head_]);
    storage_[head_].reset();
    head_ = next_index(head_);
    --size_;
    return value;
  }

  [[nodiscard]] T* front() {
    if (empty()) {
      return nullptr;
    }
    return &storage_[head_].value();
  }

  [[nodiscard]] const T* front() const {
    if (empty()) {
      return nullptr;
    }
    return &storage_[head_].value();
  }

  [[nodiscard]] T* back() {
    if (empty()) {
      return nullptr;
    }

    const std::size_t index = previous_index(tail_);
    return &storage_[index].value();
  }

  [[nodiscard]] const T* back() const {
    if (empty()) {
      return nullptr;
    }

    const std::size_t index = previous_index(tail_);
    return &storage_[index].value();
  }

  void clear() {
    while (pop()) {
    }
  }

  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

  [[nodiscard]] bool full() const noexcept { return size_ == capacity_; }

  [[nodiscard]] std::size_t size() const noexcept { return size_; }

  [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }

 private:
  [[nodiscard]] std::size_t next_index(std::size_t index) const noexcept {
    return (index + 1) % capacity_;
  }

  [[nodiscard]] std::size_t previous_index(std::size_t index) const noexcept {
    return (index + capacity_ - 1) % capacity_;
  }

  std::vector<std::optional<T>> storage_;
  std::size_t capacity_;
  std::size_t head_ = 0;
  std::size_t tail_ = 0;
  std::size_t size_ = 0;
};

}  // namespace learning
