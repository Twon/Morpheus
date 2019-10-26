#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <string>
#include <vector>
#include <catch2/catch.hpp>
#include <core/cpu.hpp>

namespace morpheus::test
{

TEST_CASE("Cpu can be queried for processor info", "[morpheus.core.cpu]")
{
    cpu processor;

    // Lists of CPU and Virtual Machine vendors from https://en.wikipedia.org/wiki/CPUID
    const std::vector<std::string> expected_cpu_vendors{
        "AMDisbetter!", "AuthenticAMD", "CentaurHauls", "CyrixInstead", "GenuineIntel", "TransmetaCPU", "GenuineTMx86",
        "Geode by NSC", "NexGenDriven", "RiseRiseRise", "SiS SiS SiS ", "UMC UMC UMC ", "VIA VIA VIA ", "Vortex86 SoC"};

    const std::vector<std::string> expected_virtual_machine_vendors{"bhyve bhyve ", "KVMKVMKVM",    "Microsoft Hv",
                                                                    " lrpepyh vr",  "VMwareVMware", "XenVMMXenVMM"};

    const bool isValidCpu = std::find(std::begin(expected_cpu_vendors), std::end(expected_cpu_vendors),
                                      processor.getVendorId()) != std::end(expected_cpu_vendors);
    const bool isValidVirtualMachine =
        std::find(std::begin(expected_virtual_machine_vendors), std::end(expected_virtual_machine_vendors),
                  processor.getVendorId()) != std::end(expected_virtual_machine_vendors);

    REQUIRE((isValidCpu || isValidVirtualMachine));
    // REQUIRE(processor.getVendorId().size() == 64);
}

} // namespace morpheus::test
