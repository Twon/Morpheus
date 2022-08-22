#pragma once

#include <core/conformance/version.hpp>

#if (__cpp_lib_function_ref >= 202202L)

namespace morpheus { namespace func_ref_ns = std; }

#else

namespace morpheus::func_ref_ns 
{

template<typename F>
class function_ref
{
};

}
#endif
