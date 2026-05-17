#include "thread_pool/concurrent_queue/unbounded_queue/queue.hpp"

#include <benchmark/benchmark.h>

#include "thread_pool/base/config.hpp"

using namespace TP_NAMESPACE;

static void BMUnboundedQueue(benchmark::State& state) {
  using Task = std::move_only_function<void()>;
  unbounded::Queue<Task, LOG_SIZE> queue;
  for (TP_MAYBE_UNUSED auto _ : state) {  // NOLINT(readability-identifier-length)
    benchmark::DoNotOptimize(queue.Size());
  }
}

BENCHMARK(BMUnboundedQueue);
