#pragma once

#include <functional>

#include "thread_pool/base/config.hpp"

TP_NAMESPACE_BEGIN

using Task = std::move_only_function<void()>;

TP_NAMESPACE_END
