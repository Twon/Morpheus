#pragma once

#include <cstdint>

namespace morpheus::graph
{

/// \using NodeId
/// 
using NodeId = std::uint32_t;

/// \class Node
/// 
/// 
class Node {
public:
    consteval explicit Node(NodeId const id) noexcept : Id(id) {};

    NodeId Id;
};

} // namespace morpheus::graph