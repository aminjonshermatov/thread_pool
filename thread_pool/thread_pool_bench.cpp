#include "thread_pool/thread_pool.hpp"

#include <iostream>

auto main() -> int {
  std::cerr << tp::ThreadPool().GetWorkerCount() << std::endl;
}
