#ifndef BOUNDED_QUEUE_INL
#error "Direct inclusion of this file is not allowed, include queue.hpp"
// For the sake of sane code completion.
#include "queue.hpp"
#endif

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename T, std::size_t kLogSize>
auto Queue<T, kLogSize>::Empty() const noexcept -> std::size_t {
  const auto top = Top_.load(std::memory_order_relaxed);
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  return top >= bottom;
}

template <typename T, std::size_t kLogSize>
auto Queue<T, kLogSize>::Size() const noexcept -> std::size_t {
  const auto top = Top_.load(std::memory_order_relaxed);
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  return static_cast<std::size_t>(bottom >= top ? bottom - top : 0);
}

template <typename T, std::size_t kLogSize>
constexpr auto Queue<T, kLogSize>::Capacity() noexcept -> std::size_t {
  return kBufferSize;
}

template <typename T, std::size_t kLogSize>
template <typename U>
auto Queue<T, kLogSize>::TryPush(U&& item) -> bool {
  const auto bottom = Bottom_.load(std::memory_order_relaxed);
  const auto top = Top_.load(std::memory_order_acquire);

  if (static_cast<std::size_t>(bottom - top + 1) > kBufferSize) {
    return false;
  }

  Buffer_[bottom & kBufferMask] = std::forward<U>(item);
  Bottom_.store(bottom + 1, std::memory_order_release);
  return true;
}

template <typename T, std::size_t kLogSize>
constexpr auto Queue<T, kLogSize>::EmptyValue() noexcept -> ValueType {
  if constexpr (std::is_pointer_v<T>) {
    return static_cast<T>(nullptr);
  } else {
    return std::nullopt;
  }
}

template <typename T, std::size_t kLogSize>
auto Queue<T, kLogSize>::Pop() -> ValueType {
  const auto bottom = Bottom_.load(std::memory_order_relaxed) - 1;
  Bottom_.store(bottom, std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  auto top = Top_.load(std::memory_order_relaxed);

  if (top <= bottom) {
    const auto item = Buffer_[bottom & kBufferMask];
    if (top == bottom) {
      if (!Top_.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst,
                                        std::memory_order_relaxed)) {
        // thief stealed (from top)
        Bottom_.store(bottom + 1, std::memory_order_relaxed);
        return EmptyValue();
      }
      Bottom_.store(bottom + 1, std::memory_order_relaxed);
    }
    return item;
  }
  Bottom_.store(bottom + 1, std::memory_order_relaxed);
  return EmptyValue();
}

template <typename T, std::size_t kLogSize>
auto Queue<T, kLogSize>::Steal() -> ValueType {
  auto top = Top_.load(std::memory_order_acquire);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  const auto bottom = Bottom_.load(std::memory_order_acquire);

  if (top < bottom) {
    const auto item = Buffer_[top & kBufferMask];
    if (Top_.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst,
                                     std::memory_order_relaxed)) {
      return item;
    }
  }
  return EmptyValue();
}

}  // namespace bounded
TP_NAMESPACE_END
