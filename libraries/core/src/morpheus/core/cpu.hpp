#pragma once

#include <morpheus/core/base/architecture.hpp>
#include <morpheus/core/base/platform.hpp>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)


#if (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X86) || (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X64)

namespace morpheus
{

/// \typedef CpuidResults
///     Simple type to store the results of a call to the cpuid instruction which returns 4 registers of 32-bit size
///     (to EAX, EBX, ECX and EDX registers).
using CpuidResults = std::array<std::uint32_t, 4>;

/// \typedef CpuidLeafs
///
///
using CpuidLeafs = std::vector<CpuidResults>;

/// \class Cpu
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

#endif // (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X86) || (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X64)

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
#pragma warning(pop)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
