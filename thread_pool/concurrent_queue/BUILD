load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "queue_concept",
  hdrs = ["queue_concept.hpp"],
)

cc_library(
  name = "concurrent_queue",
  deps = [
    ":queue_concept",
    "//thread_pool/concurrent_queue/bounded_queue:queue",
    "//thread_pool/concurrent_queue/unbounded_queue:queue",
  ],
  visibility = ["//thread_pool:__pkg__"],
)
