#pragma once

#include "core/meta/concepts/aggregate.hpp"
#include <cstdint>
#include <type_traits>

namespace morpheus::meta
{

/*
template <concepts::Aggregate T>
consteval std::size_t fieldsCount()
{

    auto [...x] = T();
    return sizeof...(x);
}

template <concepts::Aggregate T>
using FieldsCount = std::integral_constant<std::size_t, fieldsCount<T>()>;
*/

} // namespace morpheus::meta