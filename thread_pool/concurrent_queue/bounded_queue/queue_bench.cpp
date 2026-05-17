#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"

#include <thread>
#include <vector>

#include <benchmark/benchmark.h>

#include "thread_pool/base/compiler_traits.hpp"

using namespace TP_NAMESPACE;

static void BM_BoundQueue_Sequential(  // NOLINT(readability-identifier-naming)
    benchmark::State& state) {
  constexpr auto kLogSize = 16;
  constexpr auto kOperationsCount = 50'000;

  bounded::Queue<int*, kLogSize> queue;
  std::vector items(kOperationsCount, 1);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    for (int iter = 0; iter < kOperationsCount; ++iter) {
      benchmark::DoNotOptimize(queue.TryPush(&items[iter]));
    }
    for (auto iter = 0U; iter < kOperationsCount; ++iter) {
      benchmark::DoNotOptimize(queue.Pop());
    }
    benchmark::DoNotOptimize(queue.Size());
  }
  state.SetItemsProcessed(state.iterations() * kOperationsCount * 2);
}
BENCHMARK(BM_BoundQueue_Sequential);

TP_ALWAYS_INLINE auto CpuRelax() -> void {
#if defined(__x86_64__)
  asm volatile("pause" ::: "memory");
#elif defined(__aarch64__)
  asm volatile("yield" ::: "memory");
#else
  std::this_thread::yield();
#endif
}

constexpr auto kLogSize = 16;
static bounded::Queue<int, kLogSize>* sharedQueue = nullptr;

static void BM_BoundQueue_Contention(  // NOLINT(readability-identifier-naming,
                                       // readability-function-cognitive-complexity)
    benchmark::State& state) {

  if (state.thread_index() == 0) {
    sharedQueue = new bounded::Queue<int, kLogSize>;
  }

  auto pushes = 0;
  auto pops = 0;
  auto steals = 0;
  auto failedSteals = 0;
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    if (state.thread_index() == 0) {
      constexpr std::size_t kOwnerIters = 10UZ;
      for (auto iter = 0; iter < kOwnerIters; ++iter) {
        if (sharedQueue->TryPush(iter)) {
          ++pushes;
        } else {
          if (auto item = sharedQueue->Pop()) {
            benchmark::DoNotOptimize(item);
            ++pops;
          }
        }
      }
    } else {
      if (auto item = sharedQueue->Steal()) {
        benchmark::DoNotOptimize(item);
        ++steals;
      } else {
        ++failedSteals;
        constexpr auto kBackoffs = 10UZ;
        for (volatile auto iter = 0; iter < kBackoffs; iter += 1) {
          CpuRelax();
        }
      }
    }
  }

  if (state.thread_index() == 0) {
    state.counters["Pushes"] = benchmark::Counter(pushes, benchmark::Counter::kIsRate);
    state.counters["Pops"] = benchmark::Counter(pops, benchmark::Counter::kIsRate);
  } else {
    state.counters["Steals"] = benchmark::Counter(steals, benchmark::Counter::kIsRate);
    state.counters["FailedSteals"] = benchmark::Counter(failedSteals, benchmark::Counter::kIsRate);
  }

  if (state.thread_index() == 0) {
    delete sharedQueue;
  }
}
BENCHMARK(BM_BoundQueue_Contention)->ThreadRange(1, 16);

static void BM_BoundQueue_Burst(  // NOLINT(readability-identifier-naming)
    benchmark::State& state) {

  if (state.thread_index() == 0) {
    sharedQueue = new bounded::Queue<int, kLogSize>;
  }

  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    if (state.thread_index() == 0) {
      constexpr auto kTasksCount = 100UZ;
      for (auto iter = 0; iter < kTasksCount; ++iter) {
        benchmark::DoNotOptimize(sharedQueue->TryPush(iter));
      }
      std::this_thread::yield();
      while (auto item = sharedQueue->Pop()) {
        benchmark::DoNotOptimize(item);
      }
    } else {
      while (auto item = sharedQueue->Pop()) {
        benchmark::DoNotOptimize(item);
        CpuRelax();
      }
    }
  }

  if (state.thread_index() == 0) {
    delete sharedQueue;
  }
}
BENCHMARK(BM_BoundQueue_Burst)->ThreadRange(1, 16);

BENCHMARK_MAIN();
