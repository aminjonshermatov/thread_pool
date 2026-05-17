Chase, David, and Yossi Lev. "Dynamic circular work-stealing deque." Proceedings of the seventeenth annual ACM symposium on Parallelism in algorithms and architectures. 2005.

```bash
bazel run //thread_pool/concurrent_queue/bounded_queue:queue_bench -c opt
```
```
Run on (8 X 2396.4 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1024 KiB (x4)
  L3 Unified 32768 KiB (x1)
Load Average: 0.41, 0.21, 0.19
----------------------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------------
BM_BoundQueue_Sequential                893591 ns       893547 ns          780 items_per_second=111.914M/s
BM_BoundQueue_Contention/threads:1        95.3 ns         95.3 ns      7378828 Pops=52.441M/s Pushes=52.5342M/s
BM_BoundQueue_Contention/threads:2        93.4 ns         93.4 ns      7516336 FailedSteals=193.738/s Pops=48.0898M/s Pushes=58.9836M/s Steals=10.7071M/s
BM_BoundQueue_Contention/threads:4         161 ns          161 ns      4448712 FailedSteals=4.79709M/s Pops=24.0162M/s Pushes=38.2729M/s Steals=13.8897M/s
BM_BoundQueue_Contention/threads:8         256 ns          255 ns      2784080 FailedSteals=14.9555M/s Pops=12.998M/s Pushes=26.2689M/s Steals=12.5314M/s
BM_BoundQueue_Contention/threads:16        396 ns          252 ns      2807840 FailedSteals=32.9924M/s Pops=6.29597M/s Pushes=33.4363M/s Steals=26.6061M/s
BM_BoundQueue_Burst/threads:1             2747 ns         2747 ns       254644
BM_BoundQueue_Burst/threads:2             1383 ns         1383 ns       507724
BM_BoundQueue_Burst/threads:4              330 ns          330 ns      2121972
BM_BoundQueue_Burst/threads:8              225 ns          225 ns      3081832
BM_BoundQueue_Burst/threads:16             250 ns          178 ns      4594544
```
