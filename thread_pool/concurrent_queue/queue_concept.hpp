#pragma once
#include <optional>

#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN

template <typename T, typename Task>
concept ConcurrentQueue = requires(T queue, Task task) {
  { queue.Push(std::move(task)) } -> std::same_as<void>;
  { queue.Pop() } -> std::same_as<std::optional<Task>>;
};

TP_NAMESPACE_END
