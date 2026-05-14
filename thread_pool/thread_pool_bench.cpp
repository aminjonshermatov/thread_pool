#include "thread_pool/thread_pool.hpp"

#include <benchmark/benchmark.h>

using namespace TP_NAMESPACE;

static void BMBoundedThreadPool(benchmark::State& state) {
  constexpr std::size_t kWorkersCount = 10UZ;
  BoundedThreadPool pool(kWorkersCount);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(pool.GetWorkerCount());
  }
}

static void BMUnBoundedThreadPool(benchmark::State& state) {
  constexpr std::size_t kWorkersCount = 10UZ;
  UnBoundedThreadPool pool(kWorkersCount);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(pool.GetWorkerCount());
  }
}

BENCHMARK(BMBoundedThreadPool);
BENCHMARK(BMUnBoundedThreadPool);
