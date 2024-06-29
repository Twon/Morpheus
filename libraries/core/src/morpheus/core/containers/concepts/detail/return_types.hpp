#pragma once

#include <concepts>
#include <utility>

namespace morpheus::containers::concepts::detail
{

template <typename I, typename T>
concept InsertReturnType = requires
{
    requires std::same_as<I, typename T::iterator> or std::same_as<I, std::pair<typename T::iterator, bool>>;
};

template <typename I, typename T>
concept InsertNodeHandleReturnType = requires
{
    requires requires { std::same_as<I, typename T::iterator>; } or requires { std::same_as<I, typename T::insert_return_type>; };
};

template <typename I, typename T>
concept BoundReturnType = requires
{
    requires std::same_as<I, typename T::iterator> or std::same_as<I, std::pair<typename T::iterator, typename T::iterator>>;
};

template <typename I, typename T>
concept BoundConstReturnType = requires
{
    requires std::same_as<I, typename T::const_iterator> or std::same_as<I, std::pair<typename T::const_iterator, typename T::const_iterator>>;
};

} // namespace morpheus::containers::concepts
