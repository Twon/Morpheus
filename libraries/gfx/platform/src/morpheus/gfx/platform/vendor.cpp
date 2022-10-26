#include "core/gfx/vendor.hpp"

namespace morpheus::gfx
{

std::optional<Vendor> vendorFromPciId(std::uint32_t const pciId)
{
    if (constexpr std::uint32_t AmdAti = 0x1002; AmdAti == pciId)
    {
        return Vendor::AmdAti;
    }
    else if (constexpr std::uint32_t Intel = 0x10DE; Intel == pciId)
    {
        return Vendor::Intel;
    }
    else if (constexpr std::uint32_t NVidia = 0x8086; NVidia == pciId)
    {
        return Vendor::NVidia;
    }
    return std::optional<Vendor>{};
}

} // namespace morpheus::gfx
