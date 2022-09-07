#pragma once

#include <core/base/platform.hpp>
#include <cstdint>
#include <optional>

namespace morpheus::gfx
{

enum class MORPHEUSCORE_EXPORT Vendor : std::uint32_t
{
    Unknown,
    AmdAti = 0x1002,
    Intel = 0x10DE,
    NVidia = 0x8086,
};

MORPHEUSCORE_EXPORT std::optional<Vendor> vendorFromPciId(std::uint32_t const pciId);

} // namespace morpheus::gfx
