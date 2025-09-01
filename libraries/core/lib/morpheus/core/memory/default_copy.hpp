#pragma once

#include <memory>

namespace morpheus::memory
{

/// \struct default_copy
///     Default copier uses default allocation in conjunction with copy assignment operator of T.
template <class T>
struct default_copy
{
    /// The deleter type to be used to deallocate objects created by the copier.
    using deleter_type = std::default_delete<T>;

    /// Create a copy of the input.
    constexpr T* operator()(T const& t) const { return new T(t); }
};

} // namespace morpheus::memory
