#ifndef BOUNDED_QUEUE_INL
#error "Direct inclusion of this file is not allowed, include queue.hpp"
// For the sake of sane code completion.
#include "queue.hpp"
#endif

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename Task, std::size_t LogSize>
auto Queue<Task, LogSize>::Push(TP_MAYBE_UNUSED Task&& task) -> void { }

template <typename Task, std::size_t LogSize>
auto Queue<Task, LogSize>::Pop() -> std::optional<Task> {
  return std::nullopt;
}

template <typename Task, std::size_t LogSize>
auto Queue<Task, LogSize>::Size() const -> std::size_t {
  return 0UZ;
}

}  // namespace bounded
TP_NAMESPACE_END
