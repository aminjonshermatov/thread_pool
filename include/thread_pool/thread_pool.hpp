#pragma once

namespace tp {

class ThreadPool {
 public:
  ThreadPool(int workers = 4);
  [[nodiscard]] auto GetWorkerCount() const -> int;

 private:
  int WorkerCount_;
};

}  // namespace tp
