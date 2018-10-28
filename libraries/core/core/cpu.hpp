
#pragma once

#include <array>
#include <string>
#include <vector>
#include <core/platform.hpp>

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
using cpuid_results = std::array<uint32_t, 4>;

/*! \typedef cpuid_leafs

 */
using cpuid_leafs = std::vector<cpuid_results>;

/*! \class cpu
        This type stores information about the capabilities of the central processing unit of the current target
        system.
 */
class MORPHEUSCORE_EXPORT cpu {
public:
    //! Default constructor.
    cpu();

    //! Get the CPU vendor ID string.
    const std::string& getVendorId() const noexcept { return vendor_id; }

    //! Get the CPU brand ID string.
    const std::string& getBrandId() const noexcept { return brand_id; }

private:
    const uint32_t max_leaf;          //!< Maximum available leaf function for the cpuid instruction.
    const uint32_t max_extended_leaf; //!< Maximum available extended leaf function for the cpuid instruction.
    const cpuid_leafs leafs;          //!< Cached results of executing the standard cpuid leaf functions.
    const cpuid_leafs extended_leafs; //!< Cached results of executing the extended cpuid leaf functions.
    const std::string vendor_id;
    const std::string brand_id;
};

} // namespace morpheus

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
#pragma warning(pop)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
