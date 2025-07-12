#include <morpheus/application/po/options.hpp>
#include <morpheus/core/conformance/print.hpp>
#include <morpheus/gfx/platform/os.hpp>

using namespace morpheus;
using namespace morpheus::application::po;

int main(int argc, char* argv[])
{
    for (auto const& monitor : morpheus::gfx::os::enumerateMonitors())
    {
        print_ns::print("{}\n", monitor);
    }
}
