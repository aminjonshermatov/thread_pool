#pragma once

#include <cstddef>
#include <optional>

#include "thread_pool/base/compiler_traits.hpp"
#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename Task, std::size_t LogSize = LOG_SIZE>
class Queue {
 public:
  Queue() = default;

  auto Push(Task&& task) -> void;
  TP_NODISCARD auto Pop() -> std::optional<Task>;

  TP_NODISCARD auto Size() const -> std::size_t;

 private:
  std::size_t Size_ = 0U;
  std::size_t Capacity_ = 0U;
};

}  // namespace bounded
TP_NAMESPACE_END

#define BOUNDED_QUEUE_INL
#include "thread_pool/concurrent_queue/bounded_queue/queue-inl.hpp"
#undef BOUNDED_QUEUE_INL
