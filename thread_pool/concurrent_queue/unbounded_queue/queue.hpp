#pragma once

#include <cstddef>
#include <optional>

#include "thread_pool/base/compiler_traits.hpp"
#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN
namespace unbounded {

template <typename Task>
class Queue {
 public:
  Queue() = default;
  Queue(std::size_t capacity);

  auto Push(Task&& task) -> void;
  TP_NODISCARD auto Pop() -> std::optional<Task>;

  TP_NODISCARD auto Size() const -> std::size_t;

 private:
  std::size_t Size_ = 0U;
  std::size_t Capacity_ = 0U;
};

}  // namespace unbounded
TP_NAMESPACE_END

#define UNBOUNDED_QUEUE_INL
#include "thread_pool/concurrent_queue/unbounded_queue/queue-inl.hpp"
#undef UNBOUNDED_QUEUE_INL
