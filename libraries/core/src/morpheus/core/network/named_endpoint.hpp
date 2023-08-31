#pragma once

#include <boost/container_hash/hash.hpp>

#include <compare>
#include <cstdint>
#include <string_view>

namespace morpheus::network
{

/// \class NamedEndpoint
///     Allows for hostname to endpont resolution via DNS lookup.
class NamedEndpoint
{
public:
    NamedEndpoint(std::string_view const name, std::uint16_t const port)
    : mName(name)
    , mPort(port)
    {}

    [[nodisard]] auto name() const noexcept { return mName; }

    [[nodisard]] auto port() const noexcept { return mPort; }

    [[nodisard]] auto operator<=>(NamedEndpoint const& rhs) const noexcept = default;

private:
    std::string mName;
    std::uint16_t mPort;
};

} // namespace morpheus::network

/// std::hash specialisation for named enpoint
template <>
struct std::hash<morpheus::network::NamedEndpoint>
{
    std::size_t operator()(morpheus::network::NamedEndpoint const& n)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, n.name());
        boost::hash_combine(seed, n.port());
        return seed;
    }
};
