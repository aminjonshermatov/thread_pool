#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"

#include <benchmark/benchmark.h>

#include "thread_pool/base/compiler_traits.hpp"

using namespace TP_NAMESPACE;

static void BM_BoundQueue_Sequential(  // NOLINT(readability-identifier-naming)
    benchmark::State& state) {
  constexpr auto kLogSize = 16;
  constexpr auto kOperationsCount = 50'000;

  struct Int {
    int Val = 0;
    Int(const int val) : Val(val) { }
  };

  bounded::Queue<Int, kLogSize> queue;
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    for (int iter = 0; iter < kOperationsCount; ++iter) {
      benchmark::DoNotOptimize(queue.TryPush(Int(iter)));
    }
    for (auto iter = 0U; iter < kOperationsCount; ++iter) {
      benchmark::DoNotOptimize(queue.Pop());
    }
    benchmark::DoNotOptimize(queue.Size());
  }
  state.SetItemsProcessed(state.iterations() * kOperationsCount * 2);
}

BENCHMARK(BM_BoundQueue_Sequential);
