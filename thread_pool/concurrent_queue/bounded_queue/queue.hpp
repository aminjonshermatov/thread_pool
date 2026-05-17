#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>
#include <type_traits>

#include "thread_pool/base/compiler_traits.hpp"
#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN
namespace bounded {

template <typename T, std::size_t kLogSize>
class Queue {
  using ValueType = std::conditional_t<std::is_pointer_v<T>, T, std::optional<T>>;

 public:
  Queue() = default;
  ~Queue() = default;

  Queue(const Queue&) = delete;
  auto operator=(const Queue&) -> Queue& = delete;

  TP_NODISCARD auto Empty() const noexcept -> std::size_t;
  TP_NODISCARD auto Size() const noexcept -> std::size_t;
  static constexpr auto Capacity() noexcept -> std::size_t;

  template <typename U>
  auto TryPush(U&& item) -> bool;

  auto Pop() -> ValueType;
  auto Steal() -> ValueType;

 private:
  static constexpr auto EmptyValue() noexcept -> ValueType;

 private:
  // 2^x where x>30 more likely not OK
  static constexpr std::size_t kLogSizeUpperLimit = 30UZ;
  static_assert(std::clamp(kLogSize, 1UZ, kLogSizeUpperLimit) == kLogSize);

  static constexpr std::size_t kBufferSize = 1UZ << kLogSize;
  static constexpr std::size_t kBufferMask = kBufferSize - 1;

  CACHELINE_ALIGNED std::atomic<int64_t> Top_{0};
  CACHELINE_ALIGNED std::atomic<int64_t> Bottom_{0};

  CACHELINE_ALIGNED std::array<T, kBufferSize> Buffer_;
};

}  // namespace bounded
TP_NAMESPACE_END

#define BOUNDED_QUEUE_INL
#include "thread_pool/concurrent_queue/bounded_queue/queue-inl.hpp"
#undef BOUNDED_QUEUE_INL
