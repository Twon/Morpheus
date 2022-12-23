#pragma once

#include "morpheus/core/graph/node.hpp"

namespace morpheus::graph
{

/// \class Edge
/// 
template <typename N1, typename N2>
class Edge {
public:
    constexpr Edge() noexcept = default;

    constexpr auto getHead() noexcept { return N1{}; }
    constexpr auto getTail() noexcept { return N2{}; }

private:

};

} // namespace morpheus::graph