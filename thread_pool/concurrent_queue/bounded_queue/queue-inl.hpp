#ifndef BOUNDED_QUEUE_INL
#error "Direct inclusion of this file is not allowed, include queue.hpp"
// For the sake of sane code completion.
#include "queue.hpp"
#endif

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Empty() const noexcept -> std::size_t {
  const auto top = Top_.load(std::memory_order_relaxed);
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  return top >= bottom;
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Size() const noexcept -> std::size_t {
  const auto top = Top_.load(std::memory_order_relaxed);
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  return static_cast<std::size_t>(bottom >= top ? bottom - top : 0);
}

template <typename Task, std::size_t kLogSize>
constexpr auto Queue<Task, kLogSize>::Capacity() noexcept -> std::size_t {
  return kBufferSize;
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::TryPush(Task&& task) -> bool {
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  const auto top = Top_.load(std::memory_order_acquire);

  if (static_cast<std::size_t>(bottom - top + 1) > kBufferSize) {
    return false;
  }

  // TODO: custom allocator or placement new
  Task* taskPtr = new Task(std::move(task));
  Buffer_[bottom & kBufferMask].store(taskPtr, std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_release);
  Bottom_.store(bottom + 1, std::memory_order_relaxed);
  return true;
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Pop() -> std::optional<Task> {
  const auto bottom = Bottom_.load(std::memory_order_relaxed) - 1;
  std::atomic_thread_fence(std::memory_order_seq_cst);
  auto top = Top_.load(std::memory_order_acquire);

  if (top <= bottom) {
    auto taskPtr = Buffer_[bottom & kBufferMask].load(std::memory_order_relaxed);
    if (top == bottom) {
      if (!Top_.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst,
                                        std::memory_order_relaxed)) {
        // thief stealed (from top)
        Bottom_.store(bottom + 1, std::memory_order_relaxed);
        return std::nullopt;
      }
      Bottom_.store(bottom + 1, std::memory_order_relaxed);
    }
    return std::optional(std::move(*taskPtr));
  }
  Bottom_.store(bottom + 1, std::memory_order_relaxed);
  return std::nullopt;
}

template <typename Task, std::size_t kLogSize>
auto Queue<Task, kLogSize>::Steal() -> std::optional<Task> {
  const auto bottom = Bottom_.load(std::memory_order_acquire);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  auto top = Top_.load(std::memory_order_acquire);

  if (top < bottom) {
    auto taskPtr = Buffer_[bottom & kBufferMask].load(std::memory_order_relaxed);
    if (Top_.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst,
                                     std::memory_order_relaxed)) {
      return std::optional(std::move(*taskPtr));
    }
  }
  return std::nullopt;
}

}  // namespace bounded
TP_NAMESPACE_END
