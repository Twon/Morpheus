/// https://en.cppreference.com/w/cpp/header/functional
export namespace std
{

// [func.invoke], invoke
using std::invoke;

#if (__cpp_lib_invoke_r >= 202106L)
	using std::invoke_r;
#endif // #if (__cpp_lib_invoke_r >= 202106L)

// [refwrap], reference_wrapper
using std::reference_wrapper;

// [refwrap.common.ref], common_reference related specializations
using std::basic_common_reference;

// [arithmetic.operations], arithmetic operations
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::modulus;
using std::negate;

// [comparisons], comparisons
using std::equal_to;
using std::not_equal_to;
using std::greater;
using std::less;
using std::greater_equal;
using std::less_equal;

// [comparisons.three.way], class compare_three_way
using std::compare_three_way;

// [logical.operations], logical operations
using std::logical_and;
using std::logical_or;
using std::logical_not;

// [bitwise.operations], bitwise operations
using std::bit_and;
using std::bit_or;
using std::bit_xor;
using std::bit_not;

// [func.identity], identity
using std::identity;

// [func.not.fn], function template not_fn
using std::not_fn;

// [func.bind.partial], function templates bind_front and bind_back
using std::bind_front;
using std::bind_back;

// [func.bind], bind
using std::is_bind_expression;
using std::is_bind_expression_v;
using std::is_placeholder;
using std::is_placeholder_v;
using std::bind;

// [func.bind.place] The number M of placeholders is implementation-defined
namespace placeholders
{

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;
using std::placeholders::_6;
using std::placeholders::_7;
using std::placeholders::_8;
using std::placeholders::_9;
using std::placeholders::_10;

}

// [func.memfn], member function adaptors
using std::mem_fn;

// [func.wrap], polymorphic function wrappers
// [func.wrap.badcall], class bad_function_call
using std::bad_function_call;

// [func.wrap.func], class template function
using std::function;

// [func.wrap.func.alg], function specialized algorithms
using std::swap;

} // namespace std


/*
namespace std {

  // [func.wrap.func.nullptr], function null pointer comparison operator functions
  template<class R, class... ArgTypes>
    bool operator==(const function<R(ArgTypes...)>&, nullptr_t) noexcept;

  // [func.wrap.move], move-only wrapper
  template<class... S> class move_only_function;                        // not defined
  template<class R, class... ArgTypes>
    class move_only_function<R(ArgTypes...) cv ref noexcept(noex)>;     // see below

  // [func.wrap.copy], copyable wrapper
  template<class... S> class copyable_function;                         // not defined
  template<class R, class... ArgTypes>
    class copyable_function<R(ArgTypes...) cv ref noexcept(noex)>;      // see below

  // [func.wrap.ref], non-owning wrapper
  template<class... S> class function_ref;                              // freestanding, not defined
  template<class R, class... ArgTypes>
    class function_ref<R(ArgTypes...) cv noexcept(noex)>;               // freestanding, see below

  // [func.search], searchers
  template<class ForwardIterator1, class BinaryPredicate = equal_to<>>
    class default_searcher;                                                         // freestanding

  template<class RandomAccessIterator,
           class Hash = hash<typename iterator_traits<RandomAccessIterator>::value_type>,
           class BinaryPredicate = equal_to<>>
    class boyer_moore_searcher;

  template<class RandomAccessIterator,
           class Hash = hash<typename iterator_traits<RandomAccessIterator>::value_type>,
           class BinaryPredicate = equal_to<>>
    class boyer_moore_horspool_searcher;

  // [unord.hash], class template hash
  template<class T>
    struct hash;                                                                    // freestanding

  namespace ranges {
    // [range.cmp], concept-constrained comparisons
    struct equal_to;                                                                // freestanding
    struct not_equal_to;                                                            // freestanding
    struct greater;                                                                 // freestanding
    struct less;                                                                    // freestanding
    struct greater_equal;                                                           // freestanding
    struct less_equal;                                                              // freestanding
  }
}
*/
