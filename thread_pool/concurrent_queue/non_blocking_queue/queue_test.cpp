#include "thread_pool/concurrent_queue/non_blocking_queue/queue.hpp"

#include <gtest/gtest.h>

using namespace TP_NAMESPACE;

TEST(NonBlockingQueue, Size) {
  constexpr std::size_t kCapacity = 100UZ;
  using Task = std::move_only_function<void()>;
  non_blocking::Queue<Task> queue(kCapacity);
  EXPECT_EQ(queue.Size(), 0UZ);
}
