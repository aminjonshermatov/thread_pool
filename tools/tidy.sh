#!/bin/bash
cd "$BUILD_WORKSPACE_DIRECTORY" || exit 1

echo "Running clang-tidy..."

FILES=$(find . -type d -name "bazel-*" -prune -o \
  -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.h" \) \
  ! -name "*-inl.hpp" \
  -print)

if [ -z "$FILES" ]; then
  echo "No C++ files found."
  exit 0
fi

echo "$FILES" | xargs clang-tidy -p . --warnings-as-errors='*'

TIDY_STATUS=$?

if [ $TIDY_STATUS -ne 0 ]; then
  echo "============================================================"
  echo "❌ CLANG-TIDY FAILED! Please fix the code style issues above."
  echo "============================================================"
  exit 1
else
  echo "✅ Clang-tidy passed successfully!"
  exit 0
fi
