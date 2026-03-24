#include "learning/ring_buffer.hpp"
#include "learning/test_registry.hpp"

// 验证环形缓冲区的基本 FIFO 行为
LEARNING_TEST(ring_buffer_fifo_behavior) {
  // 容量为 3
  learning::RingBuffer<int> buffer(3);

  // 连续入队 3 个元素后应满
  LEARNING_EXPECT_TRUE(buffer.push(10));
  LEARNING_EXPECT_TRUE(buffer.push(20));
  LEARNING_EXPECT_TRUE(buffer.push(30));
  LEARNING_EXPECT_TRUE(buffer.full());
  LEARNING_EXPECT_EQ(buffer.size(), static_cast<std::size_t>(3));

  // 出队顺序应保持先进先出
  auto first = buffer.pop_value();
  LEARNING_EXPECT_TRUE(first.has_value());
  LEARNING_EXPECT_EQ(first.value(), 10);

  auto second = buffer.pop_value();
  LEARNING_EXPECT_TRUE(second.has_value());
  LEARNING_EXPECT_EQ(second.value(), 20);

  auto third = buffer.pop_value();
  LEARNING_EXPECT_TRUE(third.has_value());
  LEARNING_EXPECT_EQ(third.value(), 30);
  LEARNING_EXPECT_TRUE(buffer.empty());
}

// 验证回绕与满容量保护逻辑
LEARNING_TEST(ring_buffer_wraparound_and_capacity) {
  learning::RingBuffer<int> buffer(2);

  // 满时继续入队应失败
  LEARNING_EXPECT_TRUE(buffer.push(1));
  LEARNING_EXPECT_TRUE(buffer.push(2));
  LEARNING_EXPECT_TRUE(!buffer.push(3));

  // 出队一个后再入队，触发索引回绕
  LEARNING_EXPECT_TRUE(buffer.pop());
  LEARNING_EXPECT_TRUE(buffer.push(3));

  // 最终顺序应为 2, 3
  auto first = buffer.pop_value();
  auto second = buffer.pop_value();
  LEARNING_EXPECT_TRUE(first.has_value());
  LEARNING_EXPECT_TRUE(second.has_value());
  LEARNING_EXPECT_EQ(first.value(), 2);
  LEARNING_EXPECT_EQ(second.value(), 3);
}
