#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"

#include <gtest/gtest.h>

using namespace TP_NAMESPACE;

TEST(BoundedQueue, Size) {
  using Task = std::move_only_function<void()>;
  bounded::Queue<Task> queue{};
  EXPECT_EQ(queue.Size(), 0UZ);
}
