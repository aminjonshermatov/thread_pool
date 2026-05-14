#ifndef UNBOUNDED_QUEUE_INL
#error "Direct inclusion of this file is not allowed, include queue.hpp"
// For the sake of sane code completion.
#include "queue.hpp"
#endif

TP_NAMESPACE_BEGIN
namespace unbounded {

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Empty() const noexcept -> std::size_t {
  return {};
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Size() const noexcept -> std::size_t {
  return {};
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Capacity() const noexcept -> std::size_t {
  return {};
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::TryPush(Task&& task) -> bool {
  return {};
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Pop() -> std::optional<Task> {
  return {};
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Steal() -> std::optional<Task> {
  return {};
}

}  // namespace unbounded
TP_NAMESPACE_END
