#pragma once

#include "thread_pool/base/config.hpp"
#include "thread_pool/concurrent_queue/blocking_queue/queue.hpp"
#include "thread_pool/concurrent_queue/non_blocking_queue/queue.hpp"
#include "thread_pool/concurrent_queue/queue_concept.hpp"

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

using BlockingThreadPool = ThreadPoolImpl<blocking::Queue<Task>>;
using NonBlockingThreadPool = ThreadPoolImpl<non_blocking::Queue<Task>>;

using ThreadPool = NonBlockingThreadPool;

TP_NAMESPACE_END

#include "thread_pool/thread_pool-inl.hpp"
