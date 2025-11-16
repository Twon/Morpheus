#include <morpheus/core/conformance/date.hpp>
#include <morpheus/core/conformance/print.hpp>

using namespace morpheus;
using namespace morpheus::conf;

int main()
{
    auto const& tzdb = date::get_tzdb();
    if (tzdb.zones.empty())
    {
        print::print("Time Zone DB empty");
        return EXIT_FAILURE;
    }

    print::print("All available time zones:\n");
    for (auto& tz : tzdb.zones)
        print::print("{}\n", tz.name());

    print::print("\nAll time zone links:\n");
    for (auto& tz : tzdb.links)
        print::print("{}\n", tz.name());

    return EXIT_FAILURE;
}
