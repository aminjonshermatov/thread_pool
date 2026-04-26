load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@rules_cc//cc:defs.bzl", "cc_library")

refresh_compile_commands(
  name = "refresh_compile_commands",
)

cc_library(
  name = "thread_pool",
  srcs = glob(["src/**/*.cc"]),
  hdrs = glob(["include/thread_pool/**/*.hpp"]),
  includes = ["include"],
  visibility = ["//visibility:public"],
)
