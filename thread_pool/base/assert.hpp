#pragma once

#include <cstdlib>
#include <iostream>

#define TP_ABORT(msg)                                                  \
  do {                                                                 \
    std::cerr << "FATAL ERROR: " << (msg) << '\n'                      \
              << "File: " << __FILE__ << ":" << __LINE__ << std::endl; \
    std::abort();                                                      \
  } while (0)

#define TP_ASSERT(condition, msg) \
  do {                            \
    if (!(condition)) {           \
      TP_ABORT(msg);              \
    }                             \
  } while (0)
