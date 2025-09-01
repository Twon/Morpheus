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

    /// The name of the endpoint, typically a hostname or IP address.
    [[nodiscard]] auto name() const noexcept { return mName; }

    /// The port of the endpoint.
    [[nodiscard]] auto port() const noexcept { return mPort; }

#if defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)
    /// Compare two endpoint objects.
    [[nodiscard]] auto operator<=>(NamedEndpoint const& rhs) const noexcept = default;
#else
    /// Compare two endpoint objects.
    /// \param rhs The NamedEndpoint to compare against.
    /// \return A comparison result indicating the relative order of the NamedEndpoint objects.
    [[nodiscard]] auto operator<=>(NamedEndpoint const& rhs) const noexcept { return std::tie(mName, mPort) <=> std::tie(rhs.mName, rhs.mPort); }

    /// Equality operator for NamedEndpoint.
    /// \param rhs The NamedEndpoint to compare against.
    /// \return True if the NamedEndpoint objects are equal, false otherwise.
    [[nodiscard]] bool operator==(NamedEndpoint const& rhs) const noexcept { return std::tie(mName, mPort) == std::tie(rhs.mName, rhs.mPort); }
#endif

private:
    std::string mName;
    std::uint16_t mPort;
};

} // namespace morpheus::network

/// std::hash specialisation for named endpoint
template <>
struct std::hash<morpheus::network::NamedEndpoint>
{
    /// Hash function for NamedEndpoint
    /// \param n The NamedEndpoint to hash.
    /// \return The hash value of the NamedEndpoint.
    std::size_t operator()(morpheus::network::NamedEndpoint const& n) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, n.name());
        boost::hash_combine(seed, n.port());
        return seed;
    }
};
