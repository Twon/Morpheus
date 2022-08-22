#define CATCH_CONFIG_MAIN
#include <core/conformance/ranges.hpp>
#include <core/cpu.hpp>
#include <catch2/catch.hpp>
#include <algorithm>
#include <string>
#include <vector>


namespace morpheus::test
{

TEST_CASE("Cpu can be queried for processor info", "[morpheus.core.cpu]")
{
    Cpu processor;

    // Lists of CPU and Virtual Machine vendors from https://en.wikipedia.org/wiki/CPUID
    std::vector<std::string> const expected_cpu_vendors{
        "AMDisbetter!", "AuthenticAMD", "CentaurHauls", "CyrixInstead", "GenuineIntel", "TransmetaCPU", "GenuineTMx86",
        "Geode by NSC", "NexGenDriven", "RiseRiseRise", "SiS SiS SiS ", "UMC UMC UMC ", "VIA VIA VIA ", "Vortex86 SoC"};

    std::vector<std::string> const expectedVirtualMachineVendors{"bhyve bhyve ", "KVMKVMKVM",    "Microsoft Hv",
                                                                 " lrpepyh vr",  "VMwareVMware", "XenVMMXenVMM"};

    bool const isValidCpu = ranges::find(expected_cpu_vendors, processor.getVendorId()) != expected_cpu_vendors.end();
    bool const isValidVirtualMachine = ranges::find(expectedVirtualMachineVendors, processor.getVendorId()) != expectedVirtualMachineVendors.end();

    REQUIRE((isValidCpu || isValidVirtualMachine));
    // REQUIRE(processor.getVendorId().size() == 64);
}

} // namespace morpheus::test
