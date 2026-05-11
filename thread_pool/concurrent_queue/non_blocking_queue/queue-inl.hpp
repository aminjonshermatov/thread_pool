#pragma once

TP_NAMESPACE_BEGIN
namespace non_blocking {

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

}  // namespace non_blocking
TP_NAMESPACE_END
