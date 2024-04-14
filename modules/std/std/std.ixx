
module;

#include <any>
#include <cstdint>
#include <concepts>
#include <functional>
#include <source_location>
#include <stacktrace>
#include <string>
#include <string_view>
#include <type_traits>

export module std;

#include "any.mxx"
#include "cstdint.mxx"
#include "concepts.mxx"
#include "functional.mxx"
#include "string.mxx"
#include "source_location.mxx"
#include "stacktrace.mxx"
#include "string_view.mxx"
#include "type_traits.mxx"

#pragma warning(push)
#pragma warning(disable : 5244) // '#include <meow>' in the purview of module 'std' appears erroneous.


#pragma warning(pop)
