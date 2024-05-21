#pragma once

#if __has_include(<flat_map>)
    #include <flat_map>
#endif

// clang-format off
#if (__cpp_lib_flat_map>= 202207L)

    namespace morpheus { namespace fm_ns = std; }

#else
    #include <boost/container/flat_map.hpp>

    namespace morpheus{ namespace fm_ns = boost; }

#endif
// clang-format on
