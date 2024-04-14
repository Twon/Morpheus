// \bit.hpp Modularisation for https://eel.is/c++draft/bit.syn
export namespace std
{

// [bit.cast], bit_cast
using std::bit_cast;

// [bit.byteswap], byteswap
using std::byteswap;

// [bit.pow.two], integral powers of 2
using std::has_single_bit;
using std::bit_ceil;
using std::bit_floor;
using std::bit_width;

// [bit.rotate], rotating
using std::rotl;
using std::rotr;

// [bit.count], counting
using std::countl_zero;
using std::countl_one;
using std::countr_zero;
using std::countr_one;
using std::popcount;

// [bit.endian], endian
using std::endian;

} // namespace std
