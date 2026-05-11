#include <iostream>

#include "thread_pool/thread_pool.hpp"

using namespace TP_NAMESPACE;

auto main() -> int {
  constexpr std::size_t kWorkersCount = 5UZ;
  ThreadPool pool(kWorkersCount);
  std::cout << "Thread pool created with " << pool.GetWorkerCount() << " workers.\n";
}
