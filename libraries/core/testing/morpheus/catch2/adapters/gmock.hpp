#pragma once

namespace morpheus
{

/// Enable integration of GMock error reporting into the Catch2 test framework>
/// \param[in] argv Pass through commandline parameters for initialising GMock.
void enableGmockAdapter(char* argv[]);

} // namespace morpheus