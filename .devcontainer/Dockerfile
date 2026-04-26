FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install --no-install-recommends \
  clang \
  clangd \
  lld \
  lldb \
  llvm-18 \
  clang-format \
  clang-tidy \
  python3 \
  python3-pip \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN curl -fSsL https://github.com/bazelbuild/bazelisk/releases/download/v1.28.1/bazelisk-linux-amd64 -o /usr/local/bin/bazel \
  && chmod +x /usr/local/bin/bazel

RUN curl -fSsL https://github.com/bazelbuild/buildtools/releases/download/v8.5.1/buildifier-linux-amd64 -o /usr/local/bin/buildifier \
  && chmod +x /usr/local/bin/buildifier
