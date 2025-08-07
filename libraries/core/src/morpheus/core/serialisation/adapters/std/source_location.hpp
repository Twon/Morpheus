#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/source_location.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

namespace morpheus::serialisation::detail
{

template <concepts::WriteSerialiser Serialiser>
void serialise(Serialiser& serialiser, sl_ns::source_location const& value)
{
    serialiser.writer().beginComposite();
    serialiser.serialise("file_name", value.file_name());
    serialiser.serialise("function_name", value.function_name());
    serialiser.serialise("line", value.line());
    serialiser.serialise("column", value.column());
    serialiser.writer().endComposite();
}

} // namespace morpheus::serialisation::detail
