#include "thread_pool/thread_pool.hpp"

namespace tp {

ThreadPool::ThreadPool(int workers) : WorkerCount_(workers) {}

auto ThreadPool::GetWorkerCount() const -> int { return WorkerCount_; }

}  // namespace tp
