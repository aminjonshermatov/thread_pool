#pragma once

namespace tp {

class Deque;

class ThreadPool {
 public:
  ThreadPool(int workers = 4);
  [[nodiscard]] auto GetWorkerCount() const -> int;

 private:
  int WorkerCount_;
  Deque* Deque_;
};

}  // namespace tp
