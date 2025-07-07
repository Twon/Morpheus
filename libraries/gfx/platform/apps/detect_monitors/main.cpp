#include "morpheus/application/po/options.hpp"
#include "morpheus/core/conformance/print.hpp"
#include <morpheus/gfx/platform/win32/monitor.hpp>
#include <morpheus/gfx/platform/monitor.hpp>

using namespace morpheus;
using namespace morpheus::application::po;

int main(int argc, char* argv[])
{
    for (auto monitor : morpheus::gfx::win32::enumerateMonitors())
    {
        print_ns::print("{}\n", monitor);
    }
}
