/// \file execution.hpp
///     Modularisation for https://eel.is/c++draft/execution.syn
export namespace std
{

// [execpol.type], execution policy type trait
using std::is_execution_policy;
using std::is_execution_policy_v;

namespace execution
{
// [execpol.seq], sequenced execution policy
using std::execution::sequenced_policy;

// [execpol.par], parallel execution policy
using std::execution::parallel_policy;

// [execpol.parunseq], parallel and unsequenced execution policy
using std::execution::parallel_unsequenced_policy;

// [execpol.unseq], unsequenced execution policy
using std::execution::unsequenced_policy;

// [execpol.objects], execution policy objects

using std::execution::seq;
using std::execution::par;
using std::execution::par_unseq;
using std::execution::unseq;

}

} // namespace std
