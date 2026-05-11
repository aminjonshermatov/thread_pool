#include "thread_pool/concurrent_queue/non_blocking_queue/queue.hpp"

#include <benchmark/benchmark.h>

using namespace TP_NAMESPACE;

static void BMNonBlockingQueue(benchmark::State& state) {
  constexpr std::size_t kCapacity = 100UZ;
  using Task = std::move_only_function<void()>;
  non_blocking::Queue<Task> queue(kCapacity);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(queue.Size());
  }
}

BENCHMARK(BMNonBlockingQueue);
