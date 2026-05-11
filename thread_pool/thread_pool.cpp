#include "thread_pool/thread_pool.hpp"

#include "thread_pool/concurrent_queue/non_blocking_queue/queue.hpp"

namespace tp {

ThreadPool::ThreadPool(int workers) : WorkerCount_(workers), Deque_(new Deque) { }

auto ThreadPool::GetWorkerCount() const -> int {
  return WorkerCount_ + Deque_->Fuck();
}

}  // namespace tp
