module;

#include <morpheus/core/conformance/bit_cast.hpp>
#include <morpheus/core/conformance/coro.hpp>
#include <morpheus/core/conformance/date.hpp>
#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/core/conformance/outptr.hpp>
#include <morpheus/core/conformance/print.hpp>
#include <morpheus/core/conformance/ranges.hpp>
#include <morpheus/core/conformance/scan.hpp>
#include <morpheus/core/conformance/source_location.hpp>
#include <morpheus/core/conformance/stacktrace.hpp>
#include <morpheus/core/conformance/unreachable.hpp>
#include <morpheus/core/conformance/value_types.hpp>
#include <morpheus/core/conformance/version.hpp>

export module morpheus.core:conformance;

export namespace morpheus::conf
{

namespace exp = ::morpheus::conf::exp;
// using ::morpheus::conf::exp;

} // namespace morpheus::conf
