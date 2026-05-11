#include "thread_pool/concurrent_queue/non_blocking_queue/queue.hpp"

#include <gtest/gtest.h>

TEST(NonBlockingQueue, Fuck) {
  tp::Deque dq;
  EXPECT_EQ(dq.Fuck(), 69);
}
