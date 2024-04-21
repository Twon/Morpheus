/// \file cstddef.hpp
///     Modularisation for https://eel.is/c++draft/cstddef.syn


/*
namespace std {
  using ptrdiff_t = see below;
  using size_t = see below;
  using max_align_t = see below;
  using nullptr_t = decltype(nullptr);

  enum class byte : unsigned char {};

  // [support.types.byteops], byte type operations
  template<class IntType>
    constexpr byte& operator<<=(byte& b, IntType shift) noexcept;
  template<class IntType>
    constexpr byte operator<<(byte b, IntType shift) noexcept;
  template<class IntType>
    constexpr byte& operator>>=(byte& b, IntType shift) noexcept;
  template<class IntType>
    constexpr byte operator>>(byte b, IntType shift) noexcept;
  constexpr byte& operator|=(byte& l, byte r) noexcept;
  constexpr byte operator|(byte l, byte r) noexcept;
  constexpr byte& operator&=(byte& l, byte r) noexcept;
  constexpr byte operator&(byte l, byte r) noexcept;
  constexpr byte& operator^=(byte& l, byte r) noexcept;
  constexpr byte operator^(byte l, byte r) noexcept;
  constexpr byte operator~(byte b) noexcept;
  template<class IntType>
    constexpr IntType to_integer(byte b) noexcept;
}
*/
