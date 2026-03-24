#include "learning/ring_buffer.hpp"
#include "learning/test_registry.hpp"

LEARNING_TEST(ring_buffer_fifo_behavior) {
  learning::RingBuffer<int> buffer(3);

  LEARNING_EXPECT_TRUE(buffer.push(10));
  LEARNING_EXPECT_TRUE(buffer.push(20));
  LEARNING_EXPECT_TRUE(buffer.push(30));
  LEARNING_EXPECT_TRUE(buffer.full());
  LEARNING_EXPECT_EQ(buffer.size(), static_cast<std::size_t>(3));

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

LEARNING_TEST(ring_buffer_wraparound_and_capacity) {
  learning::RingBuffer<int> buffer(2);

  LEARNING_EXPECT_TRUE(buffer.push(1));
  LEARNING_EXPECT_TRUE(buffer.push(2));
  LEARNING_EXPECT_TRUE(!buffer.push(3));

  LEARNING_EXPECT_TRUE(buffer.pop());
  LEARNING_EXPECT_TRUE(buffer.push(3));

  auto first = buffer.pop_value();
  auto second = buffer.pop_value();
  LEARNING_EXPECT_TRUE(first.has_value());
  LEARNING_EXPECT_TRUE(second.has_value());
  LEARNING_EXPECT_EQ(first.value(), 2);
  LEARNING_EXPECT_EQ(second.value(), 3);
}
