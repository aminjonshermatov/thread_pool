#include "thread_pool/thread_pool.hpp"

#include <benchmark/benchmark.h>

using namespace TP_NAMESPACE;

static void BMBlockingThreadPool(benchmark::State& state) {
  constexpr std::size_t kWorkersCount = 10UZ;
  BlockingThreadPool pool(kWorkersCount);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(pool.GetWorkerCount());
  }
}

static void BMNonBlockingThreadPool(benchmark::State& state) {
  constexpr std::size_t kWorkersCount = 10UZ;
  NonBlockingThreadPool pool(kWorkersCount);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(pool.GetWorkerCount());
  }
}

BENCHMARK(BMBlockingThreadPool);
BENCHMARK(BMNonBlockingThreadPool);
