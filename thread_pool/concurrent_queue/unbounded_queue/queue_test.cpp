#include "thread_pool/concurrent_queue/unbounded_queue/queue.hpp"

#include <gtest/gtest.h>

using namespace TP_NAMESPACE;

TEST(UnboundedQueue, Size) {
  using Task = std::move_only_function<void()>;
  unbounded::Queue<Task> queue;
  EXPECT_EQ(queue.Size(), 0UZ);
}
