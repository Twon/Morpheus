#pragma once

#include "core/meta/complete.hpp"

namespace morpheus::meta::concepts
{

template <typename T>
concept IsComplete = is_complete_v<T>;

} // namespace morpheus::meta::concepts
