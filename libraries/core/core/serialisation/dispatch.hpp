#pragma once

namespace morpheus::serialisation
{

/// Dispatch via ADL selection, were strong methods are prefered over weak.
/// \todo 
///     Move over to tag dispatch
struct DispatchWeakTag {};
struct DispatchStrongTag : DispatchWeakTag {};
template<class> struct DispatchSelectTag : DispatchStrongTag {};

using DispatchWeak = DispatchWeakTag*;
using DispatchStrong = DispatchStrongTag*;
template<class T> using DispatchSelect = DispatchSelectTag<T>*;

}