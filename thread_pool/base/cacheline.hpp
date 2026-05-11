#pragma once

#include <new>

namespace detail {

#ifdef __cpp_lib_hardware_interference_size
inline constexpr std::size_t kCacheLineSize = std::hardware_destructive_interference_size;
#else
inline constexpr std::size_t kCacheLineSize = 64UZ;
#endif

}  // namespace detail

#define CACHELINE_ALIGNED alignas(detail::kCacheLineSize)
