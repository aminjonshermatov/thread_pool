#include "thread_pool/thread_pool.hpp"

#include <gtest/gtest.h>

TEST(ThreadPoolTest, ReturnsCorrectWorkerCount) {
  tp::ThreadPool pool;
  EXPECT_EQ(pool.GetWorkerCount(), 4);
}
