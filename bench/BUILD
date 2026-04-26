load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
  name = "thread_pool_bench",
  srcs = ["thread_pool_bench.cc"],
  deps = [
    "//:thread_pool",
    "@google_benchmark//:benchmark_main",
  ],
)
