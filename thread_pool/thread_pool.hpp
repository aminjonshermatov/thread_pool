#pragma once

#include "thread_pool/base/config.hpp"
#include "thread_pool/concurrent_queue/bounded_queue/queue.hpp"
#include "thread_pool/concurrent_queue/queue_concept.hpp"
#include "thread_pool/concurrent_queue/unbounded_queue/queue.hpp"

#include "task.hpp"

TP_NAMESPACE_BEGIN

template <ConcurrentQueue<Task> Queue>
class ThreadPoolImpl {
 public:
  ThreadPoolImpl(std::size_t workersCount);

  TP_NODISCARD auto GetWorkerCount() const -> std::size_t;

 private:
  std::size_t WorkerCount_;
  Queue Queue_;
};

using BoundedThreadPool = ThreadPoolImpl<bounded::Queue<Task>>;
using UnBoundedThreadPool = ThreadPoolImpl<unbounded::Queue<Task>>;

using ThreadPool = BoundedThreadPool;

TP_NAMESPACE_END

#define THREAD_POOL_INL
#include "thread_pool/thread_pool-inl.hpp"
#undef THREAD_POOL_INL
