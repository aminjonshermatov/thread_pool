#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>

#include "thread_pool/base/compiler_traits.hpp"
#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename Task, std::size_t kLogSize>
class Queue {
  static_assert(!std::is_pointer_v<Task>);

 public:
  Queue() = default;
  ~Queue() = default;

  Queue(const Queue&) = delete;
  auto operator=(const Queue&) -> Queue& = delete;

  TP_NODISCARD auto Empty() const noexcept -> std::size_t;
  TP_NODISCARD auto Size() const noexcept -> std::size_t;
  static constexpr auto Capacity() noexcept -> std::size_t;

  auto TryPush(Task&& task) -> bool;

  auto Pop() -> std::optional<Task>;
  auto Steal() -> std::optional<Task>;

 private:
  // 2^x where x>30 more likely not OK
  static constexpr std::size_t kLogSizeUpperLimit = 30UZ;
  static_assert(std::clamp(kLogSize, 1UZ, kLogSizeUpperLimit) == kLogSize);

  static constexpr std::size_t kBufferSize = 1UZ << kLogSize;
  static constexpr std::size_t kBufferMask = kBufferSize - 1;

  CACHELINE_ALIGNED std::atomic<int64_t> Top_;
  CACHELINE_ALIGNED std::atomic<int64_t> Bottom_;

  CACHELINE_ALIGNED std::array<std::atomic<Task*>, kBufferSize> Buffer_;
};

}  // namespace bounded
TP_NAMESPACE_END

#define BOUNDED_QUEUE_INL
#include "thread_pool/concurrent_queue/bounded_queue/queue-inl.hpp"
#undef BOUNDED_QUEUE_INL
