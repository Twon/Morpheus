#pragma once

#include <type_traits>

namespace morpheus::serialisation
{

template <typename T>
concept Reader = requires(T t)
{
    { t.isTextual() } -> std::same_as<bool>;
};

}