#pragma once

#include "morpheus/containers/concepts/archtypes/container.hpp"

#include <cstddef>
#include <compare>
#include <iterator>

namespace morpheus::containers::concepts::archtypes
{

// Pull range access functions into scope. 
using std::rbegin;
using std::rend;
using std::crbegin;
using std::crend;

struct Reversible : Container
{
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr reverse_iterator rbegin() noexcept;
    constexpr reverse_iterator rend() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
};

} // namespace morpheus::containers::concepts::archtypes 
