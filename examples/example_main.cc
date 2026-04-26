#include <iostream>

#include "thread_pool/thread_pool.hpp"

auto main() -> int {
  tp::ThreadPool pool;
  std::cout << "Thread pool created with " << pool.GetWorkerCount() << " workers.\n";
  return 0;
}
