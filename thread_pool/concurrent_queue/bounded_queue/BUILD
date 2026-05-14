load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary", "cc_test")

cc_library(
  name = "queue",
  hdrs = [
    "queue.hpp",
    "queue-inl.hpp",
  ],
  visibility = ["//thread_pool:__subpackages__"],
  deps = ["//thread_pool/base:base"],
)

cc_test(
  name = "queue_test",
  srcs = ["queue_test.cpp"],
  deps = [
    "//thread_pool/concurrent_queue/bounded_queue:queue", 
    "@googletest//:gtest_main",
  ],
)

cc_binary(
  name = "queue_bench",
  srcs = ["queue_bench.cpp"],
  deps = [
    "//thread_pool/concurrent_queue/bounded_queue:queue", 
    "@google_benchmark//:benchmark_main",
  ],
)
