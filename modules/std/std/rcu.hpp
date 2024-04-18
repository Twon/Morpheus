/// \file rcu.hpp
///     Modularisation for https://eel.is/c++draft/rcu.syn
export namespace std
{

// [saferecl.rcu.base], class template rcu_obj_base
using std::rcu_obj_base;

// [saferecl.rcu.domain], class rcu_domain
using std::rcu_domain;

// [saferecl.rcu.domain.func] non-member functions
using std::rcu_default_domain;
using std::rcu_synchronize;
using std::rcu_barrier;
using std::rcu_retire;

} // namespace std
