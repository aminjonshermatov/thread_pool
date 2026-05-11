#pragma once

#if defined(__GNUC__) || defined(__clang__)
#define TP_LIKELY(x) __builtin_expect(!!(x), 1)
#define TP_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define TP_LIKELY(x) (x)
#define TP_UNLIKELY(x) (x)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define TP_ALWAYS_INLINE inline __attribute__((always_inline))
#define TP_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define TP_ALWAYS_INLINE __forceinline
#define TP_NOINLINE __declspec(noinline)
#else
#define TP_ALWAYS_INLINE inline
#define TP_NOINLINE
#endif

#if defined(__GNUC__) || defined(__clang__)
#define TP_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#define TP_UNREACHABLE() __assume(0)
#else
#include <cstdlib>
#define TP_UNREACHABLE() std::abort()
#endif

#ifdef __has_cpp_attribute
#define TP_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define TP_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if TP_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907L
#define TP_NODISCARD [[nodiscard]]
#define TP_NODISCARD_MSG(msg) [[nodiscard(msg)]]

#elif TP_HAS_CPP_ATTRIBUTE(nodiscard) >= 201603L
#define TP_NODISCARD [[nodiscard]]
#define TP_NODISCARD_MSG(msg) [[nodiscard]]

#elif defined(__GNUC__) || defined(__clang__)
#define TP_NODISCARD __attribute__((warn_unused_result))
#define TP_NODISCARD_MSG(msg) __attribute__((warn_unused_result))

#elif defined(_MSC_VER) && _MSC_VER >= 1700
#define TP_NODISCARD _Check_return_
#define TP_NODISCARD_MSG(msg) _Check_return_

#else
#define TP_NODISCARD
#define TP_NODISCARD_MSG(msg)
#endif

#if TP_HAS_CPP_ATTRIBUTE(maybe_unused) >= 201603L
#define TP_MAYBE_UNUSED [[maybe_unused]]
#elif defined(__GNUC__) || defined(__clang__)
#define TP_MAYBE_UNUSED __attribute__((unused))
#else
#define TP_MAYBE_UNUSED
#endif
