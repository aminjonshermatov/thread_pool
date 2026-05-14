#pragma once

#include <cstddef>
#include <new>

namespace detail {

#ifdef __cpp_lib_hardware_interference_size
inline constexpr std::size_t kCacheLineSize = std::hardware_destructive_interference_size;
#else
inline constexpr std::size_t kCacheLineSize = 64UZ;
#endif

inline constexpr std::size_t kLogSize = 10UZ;

}  // namespace detail

#define CACHELINE_ALIGNED alignas(detail::kCacheLineSize)

#ifndef LOG_SIZE
#define LOG_SIZE detail::kLogSize
#endif

#define CONFIG_IN
#include "thread_pool/base/config.hpp.in"
#undef CONFIG_IN
