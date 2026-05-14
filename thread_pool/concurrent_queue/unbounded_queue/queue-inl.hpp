#ifndef UNBOUNDED_QUEUE_INL
#error "Direct inclusion of this file is not allowed, include queue.hpp"
// For the sake of sane code completion.
#include "queue.hpp"
#endif

TP_NAMESPACE_BEGIN
namespace unbounded {

template <typename Task>
Queue<Task>::Queue(std::size_t capacity) : Capacity_(capacity) { }

template <typename Task>
auto Queue<Task>::Push(TP_MAYBE_UNUSED Task&& task) -> void { }

template <typename Task>
auto Queue<Task>::Pop() -> std::optional<Task> {
  return std::nullopt;
}

template <typename Task>
auto Queue<Task>::Size() const -> std::size_t {
  return 0UZ;
}

}  // namespace unbounded
TP_NAMESPACE_END
