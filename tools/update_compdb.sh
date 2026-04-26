#!/bin/bash
set -e

bazel run //:refresh_compile_commands

OUTPUT_BASE=$(bazel info output_base)
EXEC_ROOT=$(bazel info execution_root)
WORKSPACE=$(pwd)

cd "$OUTPUT_BASE/external"
for dir in *; do
  if [[ "$dir" == *"~"* ]]; then
    # Берем имя до первой тильды (например, googletest из googletest~1.14.0)
    base_name="${dir%%~*}"
    # Создаем симлинк (googletest~ -> googletest~1.14.0)
    ln -sf "$dir" "${base_name}~" 2>/dev/null || true
  fi
done
cd "$WORKSPACE"

sed -i "s|\"external/|\"$OUTPUT_BASE/external/|g" compile_commands.json
sed -i "s|\"bazel-out/|\"$EXEC_ROOT/bazel-out/|g" compile_commands.json
sed -i "s|\"file\": \"|\"file\": \"$WORKSPACE/|g" compile_commands.json
