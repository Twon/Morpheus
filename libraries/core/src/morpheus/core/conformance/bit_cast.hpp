#pragma once

// clang-format off
#if __has_include(<bit>)
    #include <bit> // IWYU pragma: export
#endif

#if ( __cpp_lib_bit_cast >= 201806L )
    namespace morpheus { namespace bit_ns = std; }
#else
    namespace morpheus {
        namespace core::bit
        {
            template<class To, class From>
            requires{
                sizeof(To) == sizeof(From);
                std::is_trivially_copyable_v<From>
                std::is_trivially_copyable_v<To>
            }
            To bit_cast(From const& src) noexcept
            {
                static_assert(std::is_trivially_constructible_v<To>, "This implementation additionally requires destination type to be trivially constructible");

                To dst;
                std::memcpy(&dst, &src, sizeof(To));
                return dst;
            }
        }
        namespace bit_ns = core::bit;
    }
#endif
// clang-format on
