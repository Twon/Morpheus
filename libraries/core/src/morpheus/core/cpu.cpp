#include "morpheus/core/base/platform.hpp"
#include <morpheus/core/cpu.hpp>

#if (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X86) || (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X64)

#if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
#include <cpuid.h>
#elif (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
#include <intrin.h>
#endif

#include <algorithm>
#include <cstring>

namespace morpheus
{

namespace
{

constexpr std::uint32_t extended_leaf_range_start = 0x80000000;
constexpr std::uint32_t extended_leaf_range_mask = ~extended_leaf_range_start;

//---------------------------------------------------------------------------------------------------------------------

/*!

   @param[in] leaf
   @param[in] subleaf
   @return

 */
auto cpuid(std::uint32_t const leaf, std::uint32_t const subleaf = 0)
{
    CpuidResults results;
#if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
    __get_cpuid(leaf, &results[0], &results[1], &results[2], &results[3]);
#elif (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    std::array<int32_t, 4> result_leaf;
    __cpuidex(&result_leaf[0], static_cast<std::int32_t>(leaf), static_cast<std::int32_t>(subleaf));
    results[0] = static_cast<std::uint32_t>(result_leaf[0]);
    results[1] = static_cast<std::uint32_t>(result_leaf[1]);
    results[2] = static_cast<std::uint32_t>(result_leaf[2]);
    results[3] = static_cast<std::uint32_t>(result_leaf[3]);
#endif
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

auto get_max_leaf_function()
{
    return cpuid(0)[0];
}

//---------------------------------------------------------------------------------------------------------------------

auto get_max_extended_leaf_function()
{
    return cpuid(extended_leaf_range_start)[0];
}

//---------------------------------------------------------------------------------------------------------------------

auto query_leaf_functions(const std::uint32_t max_leaf)
{
    CpuidLeafs results(max_leaf);
    std::uint32_t current_leaf = 0;
    std::generate(results.begin(), results.end(), [&]() { return cpuid(current_leaf++); });
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

auto query_extended_leaf_functions(const std::uint32_t max_extended_leaf)
{
    CpuidLeafs results(extended_leaf_range_mask & max_extended_leaf);
    std::uint32_t current_leaf = 0;
    std::generate(results.begin(), results.end(), [&]() { return cpuid(extended_leaf_range_start | current_leaf++); });
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

auto query_vendor_id(CpuidLeafs const& cached_leafs)
{
    std::array<char, 16> string_buffer;
    std::memset(&string_buffer[0], 0, sizeof(string_buffer));
    std::memcpy(&string_buffer[0], &cached_leafs[0][1], sizeof(std::uint32_t));
    std::memcpy(&string_buffer[4], &cached_leafs[0][3], sizeof(std::uint32_t));
    std::memcpy(&string_buffer[8], &cached_leafs[0][2], sizeof(std::uint32_t));
    return std::string(string_buffer.data());
}

//---------------------------------------------------------------------------------------------------------------------

auto query_brand_id(CpuidLeafs const& cached_leafs)
{
    std::array<char, 64> string_buffer;
    std::memset(&string_buffer[0], 0, sizeof(string_buffer));
    if (cached_leafs.size() >= 5)
    {
        std::memcpy(&string_buffer[0], &cached_leafs[2], sizeof(CpuidResults));
        std::memcpy(&string_buffer[16], &cached_leafs[3], sizeof(CpuidResults));
        std::memcpy(&string_buffer[32], &cached_leafs[4], sizeof(CpuidResults));
    }
    return std::string(string_buffer.data());
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace

//---------------------------------------------------------------------------------------------------------------------

Cpu::Cpu()
:   mMaxLeaf(get_max_leaf_function())
,   mMaxExtendedLeaf(get_max_extended_leaf_function())
,   mLeafs(query_leaf_functions(mMaxLeaf))
,   mExtendedLeafs(query_extended_leaf_functions(mMaxExtendedLeaf))
,   mVendorId(query_vendor_id(mLeafs))
,   mBrandId(query_brand_id(mLeafs))
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus

#endif // (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X86) || (MORPHEUS_PLATFORM_ARCHITECTURE == MORPHEUS_TARGET_ARCHITECTURE_X64)
