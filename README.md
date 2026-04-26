# Thread Pool

A simple and fast Thread Pool implementation in C++23.

## Requirements & Dependencies

The project is built using [Bazel](https://bazel.build/). All third-party dependencies are fetched automatically via Bzlmod:
* A compiler with **C++23** support (configured to use Clang)
* **Google Test** (for unit testing)
* **Google Benchmark** (for performance measuring)

## Project Structure

* `include/` & `src/` — the core library code.
* `tests/` — unit tests.
* `benchmarks/` — microbenchmarks.
* `examples/` — usage examples.

## How to Build and Run

Everything is managed via `bazel` commands. Run them from the repository root.

### Build the library
Ensures the core code compiles successfully:
```bash
bazel build //:thread_pool
```

### Run unit tests
Runs all tests in the project:
```bash
bazel test //tests/...
```

### Run benchmarks
<i>Always run benchmarks with the maximum optimization flag (-c opt), otherwise the results will be inaccurate.</i>
```bash
bazel run //benchmarks:thread_pool_bench -c opt
```

### Run examples
Build and execute the example code:
```bash
bazel run //examples:example
```

## For Developers (VS Code + Clangd)
This project is configured for a seamless VS Code experience (via DevContainers) using clangd.

Whenever you add new files or modify BUILD dependencies, update the compile_commands.json database for autocompletion by running:
```bash
./tools/update_compdb.sh
```