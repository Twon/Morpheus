#pragma once

#include <polymorphic_value.h>

namespace morpheus::memory
{

using isocpp_p0201::make_polymorphic_value;

template <typename T>
using polymorphic_value = isocpp_p0201::polymorphic_value<T>;

// template<typename T>
// class polymorphic_value
// {

// };

} // namespace morpheus::memory