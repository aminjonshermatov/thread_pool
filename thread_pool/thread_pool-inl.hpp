#ifndef THREAD_POOL_INL
#error "Direct inclusion of this file is not allowed, include thread_pool.hpp"
// For the sake of sane code completion.
#include "thread_pool.hpp"
#endif

TP_NAMESPACE_BEGIN

template <ConcurrentQueue<Task> Queue>
ThreadPoolImpl<Queue>::ThreadPoolImpl(std::size_t workersCount) : WorkerCount_(workersCount) { }

template <ConcurrentQueue<Task> Queue>
auto ThreadPoolImpl<Queue>::GetWorkerCount() const -> std::size_t {
  return WorkerCount_;
}

TP_NAMESPACE_END
