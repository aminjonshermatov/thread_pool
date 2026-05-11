load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
  name = "basic",
  srcs = ["basic.cpp"],
  deps = [
    "//thread_pool:thread_pool",
  ],
  defines = ["TP_NAMESPACE_NAME=thread_pool"],
)
