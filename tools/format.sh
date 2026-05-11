#!/bin/bash
cd "$BUILD_WORKSPACE_DIRECTORY" || exit 1

echo "Formatting C++ files..."
find . -type d -name "bazel-*" -prune -o \
  -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.h" \) \
  -print | xargs clang-format -i --style=file

echo "Done!"
