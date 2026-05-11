load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
  name = "refresh_compile_commands",
  targets = {
    "//...": "",
  },
)

sh_binary(
  name = "format",
  srcs = ["tools/format.sh"],
  tags = ["local", "executable"], 
)

sh_binary(
  name = "tidy",
  srcs = ["tools/tidy.sh"],
  tags = ["local", "executable"],
)

exports_files(["MODULE.bazel"])
