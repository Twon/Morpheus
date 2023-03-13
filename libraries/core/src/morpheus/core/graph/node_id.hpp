#pragma once

#include <string_view>

namespace morpheus::graph
{

/// \class NodeId
/// 
/// 
class NodeId {
public:
    consteval explicit Node(std::string_view const name) noexcept : mName(name) {};

    std::string_view mName;
};

} // namespace morpheus::graph