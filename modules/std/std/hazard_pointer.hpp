/// \file hazard_pointer.hpp
///     Modularisation for https://eel.is/c++draft/hazard.pointer.syn
export namespace std
{

// [saferecl.hp.base], class template hazard_pointer_obj_base
using std::hazard_pointer_obj_base;

// [saferecl.hp.holder], class hazard_pointer
using std::hazard_pointer;

// [saferecl.hp.holder.nonmem], non-member functions
using std::make_hazard_pointer;
using std::swap;

} // namespace std
