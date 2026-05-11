#pragma once

TP_NAMESPACE_BEGIN

template <ConcurrentQueue<Task> Queue>
ThreadPoolImpl<Queue>::ThreadPoolImpl(std::size_t workersCount) : WorkerCount_(workersCount) { }

template <ConcurrentQueue<Task> Queue>
auto ThreadPoolImpl<Queue>::GetWorkerCount() const -> std::size_t {
  return WorkerCount_;
}

TP_NAMESPACE_END
