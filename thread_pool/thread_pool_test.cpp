#include "thread_pool/thread_pool.hpp"

#include <gtest/gtest.h>

#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN

TEST(DefaultThreadPoolTest, ReturnsCorrectWorkerCount) {
  constexpr std::size_t kWorkersCount = 10UZ;
  ThreadPool pool(kWorkersCount);
  EXPECT_EQ(pool.GetWorkerCount(), kWorkersCount);
}

TEST(BoundedThreadPoolTest, ReturnsCorrectWorkerCount) {
  constexpr std::size_t kWorkersCount = 10UZ;
  BoundedThreadPool pool(kWorkersCount);
  EXPECT_EQ(pool.GetWorkerCount(), kWorkersCount);
}

TEST(UnBoundedThreadPoolTest, ReturnsCorrectWorkerCount) {
  constexpr std::size_t kWorkersCount = 10UZ;
  UnBoundedThreadPool pool(kWorkersCount);
  EXPECT_EQ(pool.GetWorkerCount(), kWorkersCount);
}

TP_NAMESPACE_END
