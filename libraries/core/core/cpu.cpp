#include <core/platform.hpp>

#if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
#include <cpuid.h>
#elif (MORPHEUS_IS_VISUALSTUDIO_COMPILER)
#include <intrin.h>
#endif

#include <core/cpu.hpp>


namespace morpheus
{

namespace
{

constexpr uint32_t extended_leaf_range_start = 0x80000000;
constexpr uint32_t extended_leaf_range_mask = ~extended_leaf_range_start;

//---------------------------------------------------------------------------------------------------------------------

/*!

   @param[in] leaf
   @param[in] subleaf
   @return

 */
const auto cpuid(const uint32_t leaf, const uint32_t subleaf = 0)
{
    cpuid_results results;
#if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
    __get_cpuid(leaf, &results[0], &results[1], &results[2], &results[3]);
#elif (MORPHEUS_IS_VISUALSTUDIO_COMPILER)
    std::array<int32_t, 4> result_leaf;
    __cpuidex(&result_leaf[0], static_cast<int32_t>(leaf), static_cast<int32_t>(subleaf));
    results[0] = static_cast<uint32_t>(result_leaf[0]);
    results[1] = static_cast<uint32_t>(result_leaf[1]);
    results[2] = static_cast<uint32_t>(result_leaf[2]);
    results[3] = static_cast<uint32_t>(result_leaf[3]);
#endif
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

const auto get_max_leaf_function()
{
    return cpuid(0)[0];
}

//---------------------------------------------------------------------------------------------------------------------

const auto get_max_extended_leaf_function()
{
    return cpuid(extended_leaf_range_start)[0];
}

//---------------------------------------------------------------------------------------------------------------------

const auto query_leaf_functions(const uint32_t max_leaf)
{
    cpuid_leafs results(max_leaf);
    uint32_t current_leaf = 0;
    std::generate(results.begin(), results.end(), [&]() { return cpuid(current_leaf++); });
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

const auto query_extended_leaf_functions(const uint32_t max_extended_leaf)
{
    cpuid_leafs results(extended_leaf_range_mask & max_extended_leaf);
    uint32_t current_leaf = 0;
    std::generate(results.begin(), results.end(), [&]() { return cpuid(extended_leaf_range_start | current_leaf++); });
    return results;
}

//---------------------------------------------------------------------------------------------------------------------

const auto query_vendor_id(const cpuid_leafs& cached_leafs)
{
    std::array<char, 16> string_buffer;
    memset(&string_buffer[0], 0, sizeof(string_buffer));
    memcpy(&string_buffer[0], &cached_leafs[0][1], sizeof(uint32_t));
    memcpy(&string_buffer[4], &cached_leafs[0][3], sizeof(uint32_t));
    memcpy(&string_buffer[8], &cached_leafs[0][2], sizeof(uint32_t));
    return std::string(string_buffer.data());
}

//---------------------------------------------------------------------------------------------------------------------

const auto query_brand_id(const cpuid_leafs& cached_leafs)
{
    std::array<char, 64> string_buffer;
    memset(&string_buffer[0], 0, sizeof(string_buffer));
    if (cached_leafs.size() >= 5)
    {
        memcpy(&string_buffer[0], &cached_leafs[2], sizeof(cpuid_results));
        memcpy(&string_buffer[16], &cached_leafs[3], sizeof(cpuid_results));
        memcpy(&string_buffer[32], &cached_leafs[4], sizeof(cpuid_results));
    }
    return std::string(string_buffer.data());
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace

//---------------------------------------------------------------------------------------------------------------------

cpu::cpu()
: max_leaf(get_max_leaf_function()),
  max_extended_leaf(get_max_extended_leaf_function()),
  leafs(query_leaf_functions(max_leaf)),
  extended_leafs(query_extended_leaf_functions(max_extended_leaf)),
  vendor_id(query_vendor_id(leafs)),
  brand_id(query_brand_id(leafs))
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus
