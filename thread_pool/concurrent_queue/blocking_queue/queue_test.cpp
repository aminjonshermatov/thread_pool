#include "thread_pool/concurrent_queue/blocking_queue/queue.hpp"

#include <functional>

#include <gtest/gtest.h>

using namespace TP_NAMESPACE;

TEST(BlockingQueue, Size) {
  constexpr std::size_t kCapacity = 100UZ;
  using Task = std::move_only_function<void()>;
  blocking::Queue<Task> queue(kCapacity);
  EXPECT_EQ(queue.Size(), 0UZ);
}
