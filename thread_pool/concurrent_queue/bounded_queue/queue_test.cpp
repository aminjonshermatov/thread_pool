#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <barrier>
#include <cstdint>
#include <functional>
#include <optional>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

#include "thread_pool/base/config.hpp"

using namespace TP_NAMESPACE;

TEST(BoundedQueueTests, Empty) {
  bounded::Queue<int, 1> queue;
  ASSERT_EQ(queue.Pop(), std::nullopt);
  ASSERT_EQ(queue.Steal(), std::nullopt);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, BasicPushPop) {
  bounded::Queue<int*, 1> queue;
  ASSERT_TRUE(queue.Empty());

  auto item = 1;
  ASSERT_TRUE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_FALSE(queue.Empty());

  ASSERT_EQ(queue.Pop(), &item);
  ASSERT_EQ(queue.Size(), 0UZ);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, BasicPushSteal) {
  bounded::Queue<int*, 1> queue;
  ASSERT_TRUE(queue.Empty());

  auto item = 1;
  ASSERT_TRUE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_FALSE(queue.Empty());

  ASSERT_EQ(queue.Steal(), &item);
  ASSERT_EQ(queue.Size(), 0UZ);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, Owerflow) {
  bounded::Queue<int*, 1> queue;
  ASSERT_TRUE(queue.Empty());

  auto item = 1;
  ASSERT_TRUE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 1UZ);

  ASSERT_TRUE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_FALSE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_NE(queue.Pop(), nullptr);
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_TRUE(queue.TryPush(&item));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_NE(queue.Pop(), nullptr);
  ASSERT_NE(queue.Pop(), nullptr);
}

TEST(BoundedQueueTests, Orders) {
  bounded::Queue<int*, 2> queue;

  std::array items{1, 2, 3};
  ASSERT_TRUE(queue.TryPush(&items[0]));  // NOLINT(readability-container-data-pointer)
  ASSERT_TRUE(queue.TryPush(&items[1]));
  ASSERT_TRUE(queue.TryPush(&items[2]));

  ASSERT_EQ(queue.Size(), 3);

  ASSERT_EQ(queue.Pop(), &items[2]);
  ASSERT_EQ(queue.Size(), 2);

  ASSERT_EQ(queue.Steal(), &items[0]);  // NOLINT(readability-container-data-pointer)
  ASSERT_EQ(queue.Size(), 1);

  ASSERT_EQ(queue.Pop(), &items[1]);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, WrapAround) {
  bounded::Queue<int, 3> queue;

  constexpr uint8_t kIters = 100U;
  for (auto iter = 0U; iter < kIters; ++iter) {
    ASSERT_TRUE(queue.TryPush(iter));
    ASSERT_EQ(queue.Pop().value(), iter);
  }
}

TEST(BoundedQueueTests, StressTestExactlyOnceExecution) {
  constexpr auto kTaskCount = 100'000UZ;
  constexpr auto kThievesCount = 5UZ;

  constexpr auto kLogSize = 10UZ;
  bounded::Queue<int, kLogSize> queue;

  std::atomic<bool> producersDone{false};

  std::array<std::jthread, kThievesCount> thieves;
  std::vector<std::atomic<uint32_t>> results(kTaskCount);
  std::ranges::generate(thieves, [&producersDone, &queue, &results] {
    return std::jthread([&producersDone, &queue, &results] {
      while (!producersDone.load(std::memory_order::acquire)) {
        if (auto taskId = queue.Steal()) {
          results[taskId.value()].fetch_add(taskId.value(), std::memory_order::relaxed);
        } else {
          std::this_thread::yield();
        }
      }
      while (auto taskId = queue.Steal()) {
        results[taskId.value()].fetch_add(taskId.value(), std::memory_order::relaxed);
      }
    });
  });

  std::ranges::generate(results, [] { return 0U; });
  for (auto taskId = 0; taskId < kTaskCount; ++taskId) {
    while (!queue.TryPush(taskId)) {
      if (auto localTaskId = queue.Pop()) {
        results[localTaskId.value()].fetch_add(localTaskId.value(), std::memory_order::relaxed);
      }
    }
  }

  producersDone.store(true, std::memory_order::release);
  for (auto& thief : thieves) {
    if (thief.joinable()) {
      thief.join();
    }
  }

  for (auto taskId = 0; taskId < kTaskCount; ++taskId) {
    ASSERT_EQ(results[taskId], taskId);
  }
}

TEST(BoundedQueueTests, RaceForLastElement) {
  std::barrier syncPoint(2);

  std::atomic<int> popSuccess{0};
  std::atomic<int> stealSuccess{0};

  bounded::Queue<bool, 2> queue;
  queue.TryPush(true);

  std::jthread thief([&stealSuccess, &queue, &syncPoint] {
    syncPoint.arrive_and_wait();
    if (TP_MAYBE_UNUSED auto item = queue.Steal()) {
      stealSuccess.fetch_add(1);
    }
  });

  syncPoint.arrive_and_wait();
  if (TP_MAYBE_UNUSED auto item = queue.Pop()) {
    popSuccess.fetch_add(1);
  }

  thief.join();
  const auto total = popSuccess.load() + stealSuccess.load();
  ASSERT_EQ(total, 1);
}
