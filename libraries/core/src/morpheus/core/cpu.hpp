#pragma once

#include <core/base/platform.hpp>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)

namespace morpheus
{

/*! \typedef cpuid_results
        Simple type to store the results of a call to the cpuid instruction which returns 4 registers of 32-bit size
        (to EAX, EBX, ECX and EDX registers).
 */
using CpuidResults = std::array<uint32_t, 4>;

/*! \typedef cpuid_leafs

 */
using CpuidLeafs = std::vector<CpuidResults>;

/// \class cpu
///     This type stores information about the capabilities of the central processing unit of the current target
///     system.
///
class MORPHEUSCORE_EXPORT Cpu {
public:
    //! Default constructor.
    Cpu();

    //! Get the CPU vendor ID string.
    [[nodiscard]] auto const& getVendorId() const noexcept { return mVendorId; }

    //! Get the CPU brand ID string.
    [[nodiscard]] auto const& getBrandId() const noexcept { return mBrandId; }

private:
    std::uint32_t mMaxLeaf;          //!< Maximum available leaf function for the cpuid instruction.
    std::uint32_t mMaxExtendedLeaf; //!< Maximum available extended leaf function for the cpuid instruction.
    CpuidLeafs mLeafs;          //!< Cached results of executing the standard cpuid leaf functions.
    CpuidLeafs mExtendedLeafs; //!< Cached results of executing the extended cpuid leaf functions.
    std::string mVendorId;
    std::string mBrandId;
};

} // namespace morpheus

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
#pragma warning(pop)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
