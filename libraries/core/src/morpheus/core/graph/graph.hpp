#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/graph/edge.hpp"
#include "morpheus/core/graph/node.hpp"

#include <array>
#include <concepts>

namespace morpheus::graph
{
template <typename T>
concept UniqueNodeRange = requires(T /*constinit*/ t)
{
    ranges::range<T>;
    std::same_as<std::remove_cvref_t<ranges::range_value_t<T>>, Node>;
};

template <Node... > struct NodeList {};

/// \class Graph
/// 
/// - A list of nodes
/// - Adjecency list
/// - 
class Graph {
public:
    consteval Graph() noexcept {}

    consteval Graph(UniqueNodeRange auto const& range) noexcept
    {
        
    }

//    constinit Graph(std::tuple<Node<Ids>...>) {}
private:
    auto calculateNodeList(UniqueNodeRange auto const& range) noexcept;

//    using ActualNodeLIst = decltype(calculateNodeList(UniqueNodeRange auto const& range));
};

} // namespace morpheus::graph