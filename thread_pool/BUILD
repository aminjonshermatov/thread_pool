load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary", "cc_test")

cc_library(
  name = "thread_pool",
  hdrs = [
    "thread_pool.hpp",
    "thread_pool-inl.hpp",
    "task.hpp",
  ],
  visibility = ["//visibility:public"],
  deps = [
    "//thread_pool/base:base",
    "//thread_pool/concurrent_queue:concurrent_queue",
  ],
  defines = ["TP_NAMESPACE_NAME=thread_pool"], 
)

cc_test(
  name = "thread_pool_test",
  srcs = ["thread_pool_test.cpp"],
  deps = [
    "//thread_pool:thread_pool", 
    "@googletest//:gtest_main",
  ],
)

cc_binary(
  name = "thread_pool_bench",
  srcs = ["thread_pool_bench.cpp"],
  deps = [
    "//thread_pool:thread_pool",
    "@google_benchmark//:benchmark_main",
  ],
)
