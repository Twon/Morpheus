#pragma once

#include <boost/container_hash/hash.hpp>

#include <compare>
#include <cstdint>
#include <string_view>

namespace morpheus::network
{

/// \class NamedEndpoint
///     Allows for hostname to endpoint resolution via DNS lookup.
/// \todo
///     https://stackoverflow.com/questions/31314433/how-do-i-convert-a-host-name-in-to-a-boost-address-or-endpoint
class NamedEndpoint
{
public:
    NamedEndpoint(std::string_view const name, std::uint16_t const port)
    : mName(name)
    , mPort(port)
    {}

    [[nodiscard]] auto name() const noexcept { return mName; }

    [[nodiscard]] auto port() const noexcept { return mPort; }

    [[nodiscard]] auto operator<=>(NamedEndpoint const& rhs) const noexcept = default;

private:
    std::string mName;
    std::uint16_t mPort;
};

} // namespace morpheus::network

/// std::hash specialisation for named endpoint
template <>
struct std::hash<morpheus::network::NamedEndpoint>
{
    std::size_t operator()(morpheus::network::NamedEndpoint const& n) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, n.name());
        boost::hash_combine(seed, n.port());
        return seed;
    }
};
