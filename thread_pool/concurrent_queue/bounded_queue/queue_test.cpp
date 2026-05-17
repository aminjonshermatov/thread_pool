#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <barrier>
#include <cstdint>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

#include "thread_pool/base/compiler_traits.hpp"
#include "thread_pool/base/config.hpp"

using namespace TP_NAMESPACE;

using Task = std::move_only_function<void()>;

TEST(BoundedQueueTests, Empty) {
  bounded::Queue<Task, 1> queue;
  ASSERT_FALSE(queue.Pop().has_value());
  ASSERT_FALSE(queue.Steal().has_value());
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, BasicPushPop) {
  bounded::Queue<Task, 1> queue;
  ASSERT_TRUE(queue.Empty());

  ASSERT_TRUE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_FALSE(queue.Empty());

  ASSERT_TRUE(queue.Pop());
  ASSERT_EQ(queue.Size(), 0UZ);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, BasicPushSteal) {
  bounded::Queue<Task, 1> queue;
  ASSERT_TRUE(queue.Empty());

  ASSERT_TRUE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_FALSE(queue.Empty());

  ASSERT_TRUE(queue.Steal());
  ASSERT_EQ(queue.Size(), 0UZ);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, Owerflow) {
  bounded::Queue<Task, 1> queue;
  ASSERT_TRUE(queue.Empty());

  ASSERT_TRUE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 1UZ);

  ASSERT_TRUE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_FALSE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_TRUE(queue.Pop());
  ASSERT_EQ(queue.Size(), 1UZ);
  ASSERT_TRUE(queue.TryPush([] {}));
  ASSERT_EQ(queue.Size(), 2UZ);

  ASSERT_TRUE(queue.Pop());
  ASSERT_TRUE(queue.Pop());
}

TEST(BoundedQueueTests, Orders) {
  bounded::Queue<Task, 2> queue;

  uint8_t done = 0;
  ASSERT_TRUE(queue.TryPush([&] { done |= 1 << 0; }));
  ASSERT_TRUE(queue.TryPush([&] { done |= 1 << 1; }));
  ASSERT_TRUE(queue.TryPush([&] { done |= 1 << 2; }));

  ASSERT_EQ(queue.Size(), 3);

  queue.Pop().value()();
  ASSERT_EQ(done, 0b100);
  ASSERT_EQ(queue.Size(), 2);

  queue.Steal().value()();
  ASSERT_EQ(done, 0b101);
  ASSERT_EQ(queue.Size(), 1);

  queue.Pop().value()();
  ASSERT_EQ(done, 0b111);
  ASSERT_TRUE(queue.Empty());
}

TEST(BoundedQueueTests, WrapAround) {
  bounded::Queue<Task, 3> queue;

  constexpr uint8_t kIters = 100U;
  for (auto iter = 0U; iter < kIters; ++iter) {
    uint8_t val = kIters;
    ASSERT_TRUE(queue.TryPush([&val, iter] { val = iter; }));
    if (iter % 2 == 0U) {
      queue.Pop().value()();
    } else {
      queue.Steal().value()();
    }
    ASSERT_EQ(val, iter);
  }
}

TEST(BoundedQueueTests, StressTestExactlyOnceExecution) {
  constexpr auto kTaskCount = 100'000UZ;
  constexpr auto kThievesCount = 5UZ;

  constexpr auto kLogSize = 10UZ;
  bounded::Queue<Task, kLogSize> queue;

  std::atomic<bool> producersDone{false};

  std::array<std::jthread, kThievesCount> thieves;
  std::ranges::generate(thieves, [&producersDone, &queue] {
    return std::jthread([&producersDone, &queue] {
      while (!producersDone.load(std::memory_order::acquire)) {
        if (auto task = queue.Steal()) {
          (*task)();
        } else {
          std::this_thread::yield();
        }
      }
      while (auto task = queue.Steal()) {
        (*task)();
      }
    });
  });

  std::vector<std::atomic<uint32_t>> results(kTaskCount);
  std::ranges::generate(results, [] { return 0U; });
  for (auto taskId = 0; taskId < kTaskCount; ++taskId) {
    auto task = [taskId, &results] {
      results[taskId].fetch_add(taskId, std::memory_order::relaxed);
    };
    while (!queue.TryPush(std::move(task))) {
      if (auto localTask = queue.Pop()) {
        (*localTask)();
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

  bounded::Queue<Task, 2> queue;
  queue.TryPush([] {});

  std::jthread thief([&stealSuccess, &queue, &syncPoint] {
    syncPoint.arrive_and_wait();
    if (TP_MAYBE_UNUSED auto task = queue.Steal()) {
      stealSuccess.fetch_add(1);
    }
  });

  syncPoint.arrive_and_wait();
  if (TP_MAYBE_UNUSED auto task = queue.Pop()) {
    popSuccess.fetch_add(1);
  }

  thief.join();
  const auto total = popSuccess.load() + stealSuccess.load();
  ASSERT_EQ(total, 1);
}
