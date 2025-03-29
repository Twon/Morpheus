#pragma once

#include <cstdint>
#include <optional>

namespace morpheus::gfx
{

enum class Vendor : std::uint32_t
{
    Unknown,
    AmdAti = 0x1002,
    Apple = 0x106B,
    Intel = 0x10DE,
    NVidia = 0x8086
};

std::optional<Vendor> vendorFromPciId(std::uint32_t const pciId);

} // namespace morpheus::gfx
