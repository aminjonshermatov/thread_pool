#include "thread_pool/concurrent_queue/unbounded_queue/queue.hpp"

#include <gtest/gtest.h>

#include "thread_pool/base/config.hpp"

using namespace TP_NAMESPACE;

using Task = std::move_only_function<void()>;

TEST(UnboundedQueue, Size) {
  unbounded::Queue<Task, LOG_SIZE> queue;
  EXPECT_EQ(queue.Size(), 0UZ);
}
