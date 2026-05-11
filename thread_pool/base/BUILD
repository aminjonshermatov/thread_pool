load("@rules_cc//cc:defs.bzl", "cc_library")


cc_library(
  name = "assert",
  hdrs = ["assert.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "cacheline",
  hdrs = ["cacheline.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "thread_annotations",
  hdrs = ["thread_annotations.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "compiler_traits",
  hdrs = ["compiler_traits.hpp"],
  visibility = ["//visibility:public"],
)

genrule(
  name = "generate_config",
  srcs = ["//:MODULE.bazel"],
  outs = ["config.hpp"],
  cmd = """
    RAW_VERSION=$$(sed -n 's/.*version = "\\([^\\"]*\\)".*/\\1/p' $< | head -n 1)
    NS_VERSION=$$(echo $$RAW_VERSION | tr '.' '_')

    echo "#pragma once" > $@
    echo "" >> $@
    echo "#define TP_VERSION_STR \\"$$RAW_VERSION\\"" >> $@
    echo "" >> $@

    echo "#ifndef TP_NAMESPACE_NAME" >> $@
    echo "#define TP_NAMESPACE_NAME tp" >> $@
    echo "#endif" >> $@
    echo "" >> $@

    echo "#define TP_NAMESPACE_BEGIN \\\\" >> $@
    echo "  namespace TP_NAMESPACE_NAME { \\\\" >> $@
    echo "  inline namespace v$$NS_VERSION {" >> $@
    echo "" >> $@

    echo "#define TP_NAMESPACE TP_NAMESPACE_NAME" >> $@

    echo "#define TP_NAMESPACE_END } }" >> $@
  """,
)

cc_library(
  name = "config",
  hdrs = ["config.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "base",
  deps = [
    ":assert",
    ":cacheline",
    ":config",
    ":compiler_traits",
    ":thread_annotations",
  ],
  visibility = ["//visibility:public"],
)
