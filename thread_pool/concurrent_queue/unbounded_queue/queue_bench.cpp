#include "thread_pool/concurrent_queue/unbounded_queue/queue.hpp"

#include <benchmark/benchmark.h>

using namespace TP_NAMESPACE;

static void BMUnboundedQueue(benchmark::State& state) {
  constexpr std::size_t kCapacity = 100UZ;
  using Task = std::move_only_function<void()>;
  unbounded::Queue<Task> queue(kCapacity);
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(queue.Size());
  }
}

BENCHMARK(BMUnboundedQueue);
