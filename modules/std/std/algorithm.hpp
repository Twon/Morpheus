/// \algorithm.hpp Modularisation for https://eel.is/c++draft/algorithm.syn
export namespace std
{

namespace ranges
{

// [algorithms.results], algorithm result types
using std::ranges::in_fun_result;
using std::ranges::in_in_result;
using std::ranges::in_out_result;
using std::ranges::in_in_out_result;
using std::ranges::in_out_out_result;
using std::ranges::min_max_result;
using std::ranges::in_found_result;
using std::ranges::in_value_result;
using std::ranges::out_value_result;

}

// [alg.nonmodifying], non-modifying sequence operations
// [alg.all.of], all of
using std::all_of;

namespace ranges
{

using std::ranges::all_of;

}

// [alg.any.of], any of
using std::any_of;

namespace ranges
{

using std::ranges::any_of;

}

// [alg.none.of], none of
using std::none_of;

namespace ranges
{

using std::ranges::none_of;

}

#if (__cpp_lib_ranges_contains >= 202207L)
    namespace ranges
    {

        using std::ranges::contains;
        using std::ranges::contains_subrange;

    }
#endif // #if (__cpp_lib_ranges_contains >= 202207L)

// [alg.foreach], for each
using std::for_each;
using std::for_each_n;

namespace ranges
{

using std::ranges::for_each;
using std::ranges::for_each_result;
using std::ranges::for_each_n;
using std::ranges::for_each_n_result;

}

// [alg.find], find
using std::find;
using std::find_if;
using std::find_if_not;

namespace ranges
{

using std::ranges::find;
using std::ranges::find_if;
using std::ranges::find_if_not;

} // namespace ranges

// [alg.find.last], find last
namespace ranges
{

using std::ranges::find_last;
using std::ranges::find_last_if;
using std::ranges::find_last_if_not;

} // namespace ranges

// [alg.find.end], find end
using std::find_end;

namespace ranges
{

using std::ranges::find_end;

}

// [alg.find.first.of], find first
using std::find_first_of;

namespace ranges
{

using std::ranges::find_first_of;

}

// [alg.adjacent.find], adjacent find
using std::adjacent_find;

namespace ranges
{

using std::ranges::adjacent_find;

}

// [alg.count], count
using std::count;
using std::count_if;

namespace ranges
{

using std::ranges::count;
using std::ranges::count_if;

}

// [alg.mismatch], mismatch
using std::mismatch;

namespace ranges
{

using std::ranges::mismatch;
using std::ranges::mismatch_result;

} // namespace ranges

// [alg.equal], equal
using std::equal;

namespace ranges
{

using std::ranges::equal;

}

// [alg.is.permutation], is permutation
using std::is_permutation;

namespace ranges
{

using std::ranges::is_permutation;

}

// [alg.search], search
using std::search;
using std::search_n;

namespace ranges
{

using std::ranges::search;
using std::ranges::search_n;

}

namespace ranges
{

#if (__cpp_lib_ranges_starts_ends_with >= 202106L)

    // [alg.starts.with], starts with
    using std::ranges::starts_with;

    // [alg.ends.with], ends with
    using std::ranges::ends_with;

#endif // #if (__cpp_lib_ranges_starts_ends_with >= 202106L)

#if (__cpp_lib_ranges_fold >= 202207L)

    // [alg.fold], fold
    using std::ranges::fold_left;
    using std::ranges::fold_left_first;
    using std::ranges::fold_right;
    using std::ranges::fold_right_last;
    using std::ranges::fold_left_first_with_iter_result;
    using std::ranges::fold_left_first_with_iter;

#endif // #if (__cpp_lib_ranges_starts_ends_with >= 202207L)

} // namespace ranges

// [alg.modifying.operations], mutating sequence operations
// [alg.copy], copy
using std::copy;
using std::copy_n;
using std::copy_if;
using std::copy_backward;

namespace ranges
{

using std::ranges::copy;
using std::ranges::copy_result;
using std::ranges::copy_n;
using std::ranges::copy_n_result;
using std::ranges::copy_if;
using std::ranges::copy_if_result;
using std::ranges::copy_backward;
using std::ranges::copy_backward_result;

}

// [alg.move], move
using std::move;
using std::move_backward;

namespace ranges
{

using std::ranges::move;
using std::ranges::move_result;
using std::ranges::move_backward;
using std::ranges::move_backward_result;

} // namespace ranges

// [alg.swap], swap
using std::swap_ranges;

namespace ranges
{

using std::ranges::swap_ranges;
using std::ranges::swap_ranges_result;

} // namespace ranges

using std::iter_swap;

// [alg.transform], transform
using std::transform;

namespace ranges
{

using std::ranges::transform;
using std::ranges::unary_transform_result;
using std::ranges::binary_transform_result;

} // namespace ranges

} // namespace std


/*
namespace std {


  // [alg.replace], replace
  template<class ForwardIterator, class T>
    constexpr void replace(ForwardIterator first, ForwardIterator last,
                           const T& old_value, const T& new_value);
  template<class ExecutionPolicy, class ForwardIterator, class T>
    void replace(ExecutionPolicy&& exec,                        // see [algorithms.parallel.overloads]
                 ForwardIterator first, ForwardIterator last,
                 const T& old_value, const T& new_value);
  template<class ForwardIterator, class Predicate, class T>
    constexpr void replace_if(ForwardIterator first, ForwardIterator last,
                              Predicate pred, const T& new_value);
  template<class ExecutionPolicy, class ForwardIterator, class Predicate, class T>
    void replace_if(ExecutionPolicy&& exec,                     // see [algorithms.parallel.overloads]
                    ForwardIterator first, ForwardIterator last,
                    Predicate pred, const T& new_value);

  namespace ranges {
    template<input_iterator I, sentinel_for<I> S, class T1, class T2, class Proj = identity>
      requires indirectly_writable<I, const T2&> &&
               indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T1*>
      constexpr I
        replace(I first, S last, const T1& old_value, const T2& new_value, Proj proj = {});
    template<input_range R, class T1, class T2, class Proj = identity>
      requires indirectly_writable<iterator_t<R>, const T2&> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T1*>
      constexpr borrowed_iterator_t<R>
        replace(R&& r, const T1& old_value, const T2& new_value, Proj proj = {});
    template<input_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_writable<I, const T&>
      constexpr I replace_if(I first, S last, Pred pred, const T& new_value, Proj proj = {});
    template<input_range R, class T, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_writable<iterator_t<R>, const T&>
      constexpr borrowed_iterator_t<R>
        replace_if(R&& r, Pred pred, const T& new_value, Proj proj = {});
  }

  template<class InputIterator, class OutputIterator, class T>
    constexpr OutputIterator replace_copy(InputIterator first, InputIterator last,
                                          OutputIterator result,
                                          const T& old_value, const T& new_value);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2, class T>
    ForwardIterator2 replace_copy(ExecutionPolicy&& exec,       // see [algorithms.parallel.overloads]
                                  ForwardIterator1 first, ForwardIterator1 last,
                                  ForwardIterator2 result,
                                  const T& old_value, const T& new_value);
  template<class InputIterator, class OutputIterator, class Predicate, class T>
    constexpr OutputIterator replace_copy_if(InputIterator first, InputIterator last,
                                             OutputIterator result,
                                             Predicate pred, const T& new_value);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class Predicate, class T>
    ForwardIterator2 replace_copy_if(ExecutionPolicy&& exec,    // see [algorithms.parallel.overloads]
                                     ForwardIterator1 first, ForwardIterator1 last,
                                     ForwardIterator2 result,
                                     Predicate pred, const T& new_value);

  namespace ranges {
    template<class I, class O>
      using replace_copy_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, class T1, class T2,
             output_iterator<const T2&> O, class Proj = identity>
      requires indirectly_copyable<I, O> &&
               indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T1*>
      constexpr replace_copy_result<I, O>
        replace_copy(I first, S last, O result, const T1& old_value, const T2& new_value,
                     Proj proj = {});
    template<input_range R, class T1, class T2, output_iterator<const T2&> O,
             class Proj = identity>
      requires indirectly_copyable<iterator_t<R>, O> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T1*>
      constexpr replace_copy_result<borrowed_iterator_t<R>, O>
        replace_copy(R&& r, O result, const T1& old_value, const T2& new_value,
                     Proj proj = {});

    template<class I, class O>
      using replace_copy_if_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, class T, output_iterator<const T&> O,
             class Proj = identity, indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_copyable<I, O>
      constexpr replace_copy_if_result<I, O>
        replace_copy_if(I first, S last, O result, Pred pred, const T& new_value,
                        Proj proj = {});
    template<input_range R, class T, output_iterator<const T&> O, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_copyable<iterator_t<R>, O>
      constexpr replace_copy_if_result<borrowed_iterator_t<R>, O>
        replace_copy_if(R&& r, O result, Pred pred, const T& new_value,
                        Proj proj = {});
  }

  // [alg.fill], fill
  template<class ForwardIterator, class T>
    constexpr void fill(ForwardIterator first, ForwardIterator last, const T& value);
  template<class ExecutionPolicy, class ForwardIterator, class T>
    void fill(ExecutionPolicy&& exec,                           // see [algorithms.parallel.overloads]
              ForwardIterator first, ForwardIterator last, const T& value);
  template<class OutputIterator, class Size, class T>
    constexpr OutputIterator fill_n(OutputIterator first, Size n, const T& value);  // freestanding
  template<class ExecutionPolicy, class ForwardIterator,
           class Size, class T>
    ForwardIterator fill_n(ExecutionPolicy&& exec,              // see [algorithms.parallel.overloads]
                           ForwardIterator first, Size n, const T& value);

  namespace ranges {
    template<class T, output_iterator<const T&> O, sentinel_for<O> S>
      constexpr O fill(O first, S last, const T& value);
    template<class T, output_range<const T&> R>
      constexpr borrowed_iterator_t<R> fill(R&& r, const T& value);
    template<class T, output_iterator<const T&> O>
      constexpr O fill_n(O first, iter_difference_t<O> n, const T& value);
  }

  // [alg.generate], generate
  template<class ForwardIterator, class Generator>
    constexpr void generate(ForwardIterator first, ForwardIterator last,
                            Generator gen);
  template<class ExecutionPolicy, class ForwardIterator, class Generator>
    void generate(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator first, ForwardIterator last,
                  Generator gen);
  template<class OutputIterator, class Size, class Generator>
    constexpr OutputIterator generate_n(OutputIterator first, Size n, Generator gen);
  template<class ExecutionPolicy, class ForwardIterator, class Size, class Generator>
    ForwardIterator generate_n(ExecutionPolicy&& exec,          // see [algorithms.parallel.overloads]
                               ForwardIterator first, Size n, Generator gen);

  namespace ranges {
    template<input_or_output_iterator O, sentinel_for<O> S, copy_constructible F>
      requires invocable<F&> && indirectly_writable<O, invoke_result_t<F&>>
      constexpr O generate(O first, S last, F gen);
    template<class R, copy_constructible F>
      requires invocable<F&> && output_range<R, invoke_result_t<F&>>
      constexpr borrowed_iterator_t<R> generate(R&& r, F gen);
    template<input_or_output_iterator O, copy_constructible F>
      requires invocable<F&> && indirectly_writable<O, invoke_result_t<F&>>
      constexpr O generate_n(O first, iter_difference_t<O> n, F gen);
  }

  // [alg.remove], remove
  template<class ForwardIterator, class T>
    constexpr ForwardIterator remove(ForwardIterator first, ForwardIterator last,
                                     const T& value);
  template<class ExecutionPolicy, class ForwardIterator, class T>
    ForwardIterator remove(ExecutionPolicy&& exec,              // see [algorithms.parallel.overloads]
                           ForwardIterator first, ForwardIterator last,
                           const T& value);
  template<class ForwardIterator, class Predicate>
    constexpr ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                                        Predicate pred);
  template<class ExecutionPolicy, class ForwardIterator, class Predicate>
    ForwardIterator remove_if(ExecutionPolicy&& exec,           // see [algorithms.parallel.overloads]
                              ForwardIterator first, ForwardIterator last,
                              Predicate pred);

  namespace ranges {
    template<permutable I, sentinel_for<I> S, class T, class Proj = identity>
      requires indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T*>
      constexpr subrange<I> remove(I first, S last, const T& value, Proj proj = {});
    template<forward_range R, class T, class Proj = identity>
      requires permutable<iterator_t<R>> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T*>
      constexpr borrowed_subrange_t<R>
        remove(R&& r, const T& value, Proj proj = {});
    template<permutable I, sentinel_for<I> S, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      constexpr subrange<I> remove_if(I first, S last, Pred pred, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R>
        remove_if(R&& r, Pred pred, Proj proj = {});
  }

  template<class InputIterator, class OutputIterator, class T>
    constexpr OutputIterator
      remove_copy(InputIterator first, InputIterator last,
                  OutputIterator result, const T& value);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class T>
    ForwardIterator2
      remove_copy(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first, ForwardIterator1 last,
                  ForwardIterator2 result, const T& value);
  template<class InputIterator, class OutputIterator, class Predicate>
    constexpr OutputIterator
      remove_copy_if(InputIterator first, InputIterator last,
                     OutputIterator result, Predicate pred);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class Predicate>
    ForwardIterator2
      remove_copy_if(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator1 first, ForwardIterator1 last,
                     ForwardIterator2 result, Predicate pred);

  namespace ranges {
    template<class I, class O>
      using remove_copy_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, weakly_incrementable O, class T,
             class Proj = identity>
      requires indirectly_copyable<I, O> &&
               indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T*>
      constexpr remove_copy_result<I, O>
        remove_copy(I first, S last, O result, const T& value, Proj proj = {});
    template<input_range R, weakly_incrementable O, class T, class Proj = identity>
      requires indirectly_copyable<iterator_t<R>, O> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T*>
      constexpr remove_copy_result<borrowed_iterator_t<R>, O>
        remove_copy(R&& r, O result, const T& value, Proj proj = {});

    template<class I, class O>
      using remove_copy_if_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, weakly_incrementable O,
             class Proj = identity, indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_copyable<I, O>
      constexpr remove_copy_if_result<I, O>
        remove_copy_if(I first, S last, O result, Pred pred, Proj proj = {});
    template<input_range R, weakly_incrementable O, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_copyable<iterator_t<R>, O>
      constexpr remove_copy_if_result<borrowed_iterator_t<R>, O>
        remove_copy_if(R&& r, O result, Pred pred, Proj proj = {});
  }

  // [alg.unique], unique
  template<class ForwardIterator>
    constexpr ForwardIterator unique(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class BinaryPredicate>
    constexpr ForwardIterator unique(ForwardIterator first, ForwardIterator last,
                                     BinaryPredicate pred);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator unique(ExecutionPolicy&& exec,              // see [algorithms.parallel.overloads]
                           ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class BinaryPredicate>
    ForwardIterator unique(ExecutionPolicy&& exec,              // see [algorithms.parallel.overloads]
                           ForwardIterator first, ForwardIterator last,
                           BinaryPredicate pred);

  namespace ranges {
    template<permutable I, sentinel_for<I> S, class Proj = identity,
             indirect_equivalence_relation<projected<I, Proj>> C = ranges::equal_to>
      constexpr subrange<I> unique(I first, S last, C comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_equivalence_relation<projected<iterator_t<R>, Proj>> C = ranges::equal_to>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R>
        unique(R&& r, C comp = {}, Proj proj = {});
  }

  template<class InputIterator, class OutputIterator>
    constexpr OutputIterator
      unique_copy(InputIterator first, InputIterator last,
                  OutputIterator result);
  template<class InputIterator, class OutputIterator, class BinaryPredicate>
    constexpr OutputIterator
      unique_copy(InputIterator first, InputIterator last,
                  OutputIterator result, BinaryPredicate pred);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2>
    ForwardIterator2
      unique_copy(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first, ForwardIterator1 last,
                  ForwardIterator2 result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class BinaryPredicate>
    ForwardIterator2
      unique_copy(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first, ForwardIterator1 last,
                  ForwardIterator2 result, BinaryPredicate pred);

  namespace ranges {
    template<class I, class O>
      using unique_copy_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, weakly_incrementable O, class Proj = identity,
             indirect_equivalence_relation<projected<I, Proj>> C = ranges::equal_to>
      requires indirectly_copyable<I, O> &&
               (forward_iterator<I> ||
                (input_iterator<O> && same_as<iter_value_t<I>, iter_value_t<O>>) ||
                indirectly_copyable_storable<I, O>)
      constexpr unique_copy_result<I, O>
        unique_copy(I first, S last, O result, C comp = {}, Proj proj = {});
    template<input_range R, weakly_incrementable O, class Proj = identity,
             indirect_equivalence_relation<projected<iterator_t<R>, Proj>> C = ranges::equal_to>
      requires indirectly_copyable<iterator_t<R>, O> &&
               (forward_iterator<iterator_t<R>> ||
                (input_iterator<O> && same_as<range_value_t<R>, iter_value_t<O>>) ||
                indirectly_copyable_storable<iterator_t<R>, O>)
      constexpr unique_copy_result<borrowed_iterator_t<R>, O>
        unique_copy(R&& r, O result, C comp = {}, Proj proj = {});
  }

  // [alg.reverse], reverse
  template<class BidirectionalIterator>
    constexpr void reverse(BidirectionalIterator first, BidirectionalIterator last);
  template<class ExecutionPolicy, class BidirectionalIterator>
    void reverse(ExecutionPolicy&& exec,                        // see [algorithms.parallel.overloads]
                 BidirectionalIterator first, BidirectionalIterator last);

  namespace ranges {
    template<bidirectional_iterator I, sentinel_for<I> S>
      requires permutable<I>
      constexpr I reverse(I first, S last);
    template<bidirectional_range R>
      requires permutable<iterator_t<R>>
      constexpr borrowed_iterator_t<R> reverse(R&& r);
  }

  template<class BidirectionalIterator, class OutputIterator>
    constexpr OutputIterator
      reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
                   OutputIterator result);
  template<class ExecutionPolicy, class BidirectionalIterator, class ForwardIterator>
    ForwardIterator
      reverse_copy(ExecutionPolicy&& exec,                      // see [algorithms.parallel.overloads]
                   BidirectionalIterator first, BidirectionalIterator last,
                   ForwardIterator result);

  namespace ranges {
    template<class I, class O>
      using reverse_copy_result = in_out_result<I, O>;

    template<bidirectional_iterator I, sentinel_for<I> S, weakly_incrementable O>
      requires indirectly_copyable<I, O>
      constexpr reverse_copy_result<I, O>
        reverse_copy(I first, S last, O result);
    template<bidirectional_range R, weakly_incrementable O>
      requires indirectly_copyable<iterator_t<R>, O>
      constexpr reverse_copy_result<borrowed_iterator_t<R>, O>
        reverse_copy(R&& r, O result);
  }

  // [alg.rotate], rotate
  template<class ForwardIterator>
    constexpr ForwardIterator rotate(ForwardIterator first,
                                     ForwardIterator middle,
                                     ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator rotate(ExecutionPolicy&& exec,              // see [algorithms.parallel.overloads]
                           ForwardIterator first,
                           ForwardIterator middle,
                           ForwardIterator last);

  namespace ranges {
    template<permutable I, sentinel_for<I> S>
      constexpr subrange<I> rotate(I first, I middle, S last);
    template<forward_range R>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R> rotate(R&& r, iterator_t<R> middle);
  }

  template<class ForwardIterator, class OutputIterator>
    constexpr OutputIterator
      rotate_copy(ForwardIterator first, ForwardIterator middle,
                  ForwardIterator last, OutputIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2>
    ForwardIterator2
      rotate_copy(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first, ForwardIterator1 middle,
                  ForwardIterator1 last, ForwardIterator2 result);

  namespace ranges {
    template<class I, class O>
      using rotate_copy_result = in_out_result<I, O>;

    template<forward_iterator I, sentinel_for<I> S, weakly_incrementable O>
      requires indirectly_copyable<I, O>
      constexpr rotate_copy_result<I, O>
        rotate_copy(I first, I middle, S last, O result);
    template<forward_range R, weakly_incrementable O>
      requires indirectly_copyable<iterator_t<R>, O>
      constexpr rotate_copy_result<borrowed_iterator_t<R>, O>
        rotate_copy(R&& r, iterator_t<R> middle, O result);
  }

  // [alg.random.sample], sample
  template<class PopulationIterator, class SampleIterator,
           class Distance, class UniformRandomBitGenerator>
    SampleIterator sample(PopulationIterator first, PopulationIterator last,
                          SampleIterator out, Distance n,
                          UniformRandomBitGenerator&& g);

  namespace ranges {
    template<input_iterator I, sentinel_for<I> S,
             weakly_incrementable O, class Gen>
      requires (forward_iterator<I> || random_access_iterator<O>) &&
               indirectly_copyable<I, O> &&
               uniform_random_bit_generator<remove_reference_t<Gen>>
      O sample(I first, S last, O out, iter_difference_t<I> n, Gen&& g);
    template<input_range R, weakly_incrementable O, class Gen>
      requires (forward_range<R> || random_access_iterator<O>) &&
               indirectly_copyable<iterator_t<R>, O> &&
               uniform_random_bit_generator<remove_reference_t<Gen>>
      O sample(R&& r, O out, range_difference_t<R> n, Gen&& g);
  }

  // [alg.random.shuffle], shuffle
  template<class RandomAccessIterator, class UniformRandomBitGenerator>
    void shuffle(RandomAccessIterator first,
                 RandomAccessIterator last,
                 UniformRandomBitGenerator&& g);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Gen>
      requires permutable<I> &&
               uniform_random_bit_generator<remove_reference_t<Gen>>
      I shuffle(I first, S last, Gen&& g);
    template<random_access_range R, class Gen>
      requires permutable<iterator_t<R>> &&
               uniform_random_bit_generator<remove_reference_t<Gen>>
      borrowed_iterator_t<R> shuffle(R&& r, Gen&& g);
  }

  // [alg.shift], shift
  template<class ForwardIterator>
    constexpr ForwardIterator
      shift_left(ForwardIterator first, ForwardIterator last,
                 typename iterator_traits<ForwardIterator>::difference_type n);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator
      shift_left(ExecutionPolicy&& exec,                        // see [algorithms.parallel.overloads]
                 ForwardIterator first, ForwardIterator last,
                 typename iterator_traits<ForwardIterator>::difference_type n);

  namespace ranges {
    template<permutable I, sentinel_for<I> S>
      constexpr subrange<I> shift_left(I first, S last, iter_difference_t<I> n);
    template<forward_range R>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R> shift_left(R&& r, range_difference_t<R> n);
  }

  template<class ForwardIterator>
    constexpr ForwardIterator
      shift_right(ForwardIterator first, ForwardIterator last,
                  typename iterator_traits<ForwardIterator>::difference_type n);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator
      shift_right(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator first, ForwardIterator last,
                  typename iterator_traits<ForwardIterator>::difference_type n);

  namespace ranges {
    template<permutable I, sentinel_for<I> S>
      constexpr subrange<I> shift_right(I first, S last, iter_difference_t<I> n);
    template<forward_range R>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R> shift_right(R&& r, range_difference_t<R> n);
  }

  // [alg.sorting], sorting and related operations
  // [alg.sort], sorting
  template<class RandomAccessIterator>
    constexpr void sort(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void sort(RandomAccessIterator first, RandomAccessIterator last,
                        Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    void sort(ExecutionPolicy&& exec,                           // see [algorithms.parallel.overloads]
              RandomAccessIterator first, RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    void sort(ExecutionPolicy&& exec,                           // see [algorithms.parallel.overloads]
              RandomAccessIterator first, RandomAccessIterator last,
              Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        sort(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        sort(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr void stable_sort(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void stable_sort(RandomAccessIterator first, RandomAccessIterator last,
                     Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    void stable_sort(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     RandomAccessIterator first, RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    void stable_sort(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     RandomAccessIterator first, RandomAccessIterator last,
                     Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I stable_sort(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        stable_sort(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
                                RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
                                RandomAccessIterator last, Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    void partial_sort(ExecutionPolicy&& exec,                   // see [algorithms.parallel.overloads]
                      RandomAccessIterator first, RandomAccessIterator middle,
                      RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    void partial_sort(ExecutionPolicy&& exec,                   // see [algorithms.parallel.overloads]
                      RandomAccessIterator first, RandomAccessIterator middle,
                      RandomAccessIterator last, Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        partial_sort(I first, I middle, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        partial_sort(R&& r, iterator_t<R> middle, Comp comp = {},
                     Proj proj = {});
  }

  template<class InputIterator, class RandomAccessIterator>
    constexpr RandomAccessIterator
      partial_sort_copy(InputIterator first, InputIterator last,
                        RandomAccessIterator result_first,
                        RandomAccessIterator result_last);
  template<class InputIterator, class RandomAccessIterator, class Compare>
    constexpr RandomAccessIterator
      partial_sort_copy(InputIterator first, InputIterator last,
                        RandomAccessIterator result_first,
                        RandomAccessIterator result_last,
                        Compare comp);
  template<class ExecutionPolicy, class ForwardIterator, class RandomAccessIterator>
    RandomAccessIterator
      partial_sort_copy(ExecutionPolicy&& exec,                 // see [algorithms.parallel.overloads]
                        ForwardIterator first, ForwardIterator last,
                        RandomAccessIterator result_first,
                        RandomAccessIterator result_last);
  template<class ExecutionPolicy, class ForwardIterator, class RandomAccessIterator,
           class Compare>
    RandomAccessIterator
      partial_sort_copy(ExecutionPolicy&& exec,                 // see [algorithms.parallel.overloads]
                        ForwardIterator first, ForwardIterator last,
                        RandomAccessIterator result_first,
                        RandomAccessIterator result_last,
                        Compare comp);

  namespace ranges {
    template<class I, class O>
      using partial_sort_copy_result = in_out_result<I, O>;

    template<input_iterator I1, sentinel_for<I1> S1,
             random_access_iterator I2, sentinel_for<I2> S2,
             class Comp = ranges::less, class Proj1 = identity, class Proj2 = identity>
      requires indirectly_copyable<I1, I2> && sortable<I2, Comp, Proj2> &&
               indirect_strict_weak_order<Comp, projected<I1, Proj1>, projected<I2, Proj2>>
      constexpr partial_sort_copy_result<I1, I2>
        partial_sort_copy(I1 first, S1 last, I2 result_first, S2 result_last,
                          Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, random_access_range R2, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires indirectly_copyable<iterator_t<R1>, iterator_t<R2>> &&
               sortable<iterator_t<R2>, Comp, Proj2> &&
               indirect_strict_weak_order<Comp, projected<iterator_t<R1>, Proj1>,
                                          projected<iterator_t<R2>, Proj2>>
      constexpr partial_sort_copy_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>>
        partial_sort_copy(R1&& r, R2&& result_r, Comp comp = {},
                          Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class ForwardIterator>
    constexpr bool is_sorted(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class Compare>
    constexpr bool is_sorted(ForwardIterator first, ForwardIterator last,
                             Compare comp);
  template<class ExecutionPolicy, class ForwardIterator>
    bool is_sorted(ExecutionPolicy&& exec,                      // see [algorithms.parallel.overloads]
                   ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class Compare>
    bool is_sorted(ExecutionPolicy&& exec,                      // see [algorithms.parallel.overloads]
                   ForwardIterator first, ForwardIterator last,
                   Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr bool is_sorted(I first, S last, Comp comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr bool is_sorted(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator>
    constexpr ForwardIterator
      is_sorted_until(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class Compare>
    constexpr ForwardIterator
      is_sorted_until(ForwardIterator first, ForwardIterator last,
                      Compare comp);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator
      is_sorted_until(ExecutionPolicy&& exec,                   // see [algorithms.parallel.overloads]
                      ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class Compare>
    ForwardIterator
      is_sorted_until(ExecutionPolicy&& exec,                   // see [algorithms.parallel.overloads]
                      ForwardIterator first, ForwardIterator last,
                      Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr I is_sorted_until(I first, S last, Comp comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr borrowed_iterator_t<R>
        is_sorted_until(R&& r, Comp comp = {}, Proj proj = {});
  }

  // [alg.nth.element], Nth element
  template<class RandomAccessIterator>
    constexpr void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                               RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                               RandomAccessIterator last, Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    void nth_element(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     RandomAccessIterator first, RandomAccessIterator nth,
                     RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    void nth_element(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     RandomAccessIterator first, RandomAccessIterator nth,
                     RandomAccessIterator last, Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        nth_element(I first, I nth, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        nth_element(R&& r, iterator_t<R> nth, Comp comp = {}, Proj proj = {});
  }

  // [alg.binary.search], binary search
  template<class ForwardIterator, class T>
    constexpr ForwardIterator
      lower_bound(ForwardIterator first, ForwardIterator last,
                  const T& value);
  template<class ForwardIterator, class T, class Compare>
    constexpr ForwardIterator
      lower_bound(ForwardIterator first, ForwardIterator last,
                  const T& value, Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<I, Proj>> Comp = ranges::less>
      constexpr I lower_bound(I first, S last, const T& value, Comp comp = {},
                              Proj proj = {});
    template<forward_range R, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<iterator_t<R>, Proj>> Comp =
               ranges::less>
      constexpr borrowed_iterator_t<R>
        lower_bound(R&& r, const T& value, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator, class T>
    constexpr ForwardIterator
      upper_bound(ForwardIterator first, ForwardIterator last,
                  const T& value);
  template<class ForwardIterator, class T, class Compare>
    constexpr ForwardIterator
      upper_bound(ForwardIterator first, ForwardIterator last,
                  const T& value, Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<I, Proj>> Comp = ranges::less>
      constexpr I upper_bound(I first, S last, const T& value, Comp comp = {}, Proj proj = {});
    template<forward_range R, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<iterator_t<R>, Proj>> Comp =
               ranges::less>
      constexpr borrowed_iterator_t<R>
        upper_bound(R&& r, const T& value, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator, class T>
    constexpr pair<ForwardIterator, ForwardIterator>
      equal_range(ForwardIterator first, ForwardIterator last,
                  const T& value);
  template<class ForwardIterator, class T, class Compare>
    constexpr pair<ForwardIterator, ForwardIterator>
      equal_range(ForwardIterator first, ForwardIterator last,
                  const T& value, Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<I, Proj>> Comp = ranges::less>
      constexpr subrange<I>
        equal_range(I first, S last, const T& value, Comp comp = {}, Proj proj = {});
    template<forward_range R, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<iterator_t<R>, Proj>> Comp =
               ranges::less>
      constexpr borrowed_subrange_t<R>
        equal_range(R&& r, const T& value, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator, class T>
    constexpr bool
      binary_search(ForwardIterator first, ForwardIterator last,
                    const T& value);
  template<class ForwardIterator, class T, class Compare>
    constexpr bool
      binary_search(ForwardIterator first, ForwardIterator last,
                    const T& value, Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<I, Proj>> Comp = ranges::less>
      constexpr bool binary_search(I first, S last, const T& value, Comp comp = {},
                                   Proj proj = {});
    template<forward_range R, class T, class Proj = identity,
             indirect_strict_weak_order<const T*, projected<iterator_t<R>, Proj>> Comp =
               ranges::less>
      constexpr bool binary_search(R&& r, const T& value, Comp comp = {},
                                   Proj proj = {});
  }

  // [alg.partitions], partitions
  template<class InputIterator, class Predicate>
    constexpr bool is_partitioned(InputIterator first, InputIterator last, Predicate pred);
  template<class ExecutionPolicy, class ForwardIterator, class Predicate>
    bool is_partitioned(ExecutionPolicy&& exec,                 // see [algorithms.parallel.overloads]
                        ForwardIterator first, ForwardIterator last, Predicate pred);

  namespace ranges {
    template<input_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      constexpr bool is_partitioned(I first, S last, Pred pred, Proj proj = {});
    template<input_range R, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      constexpr bool is_partitioned(R&& r, Pred pred, Proj proj = {});
  }

  template<class ForwardIterator, class Predicate>
    constexpr ForwardIterator partition(ForwardIterator first,
                                        ForwardIterator last,
                                        Predicate pred);
  template<class ExecutionPolicy, class ForwardIterator, class Predicate>
    ForwardIterator partition(ExecutionPolicy&& exec,           // see [algorithms.parallel.overloads]
                              ForwardIterator first,
                              ForwardIterator last,
                              Predicate pred);

  namespace ranges {
    template<permutable I, sentinel_for<I> S, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      constexpr subrange<I>
        partition(I first, S last, Pred pred, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R>
        partition(R&& r, Pred pred, Proj proj = {});
  }

  template<class BidirectionalIterator, class Predicate>
    constexpr BidirectionalIterator stable_partition(BidirectionalIterator first,
                                                     BidirectionalIterator last,
                                                     Predicate pred);
  template<class ExecutionPolicy, class BidirectionalIterator, class Predicate>
    BidirectionalIterator stable_partition(ExecutionPolicy&& exec,  // see [algorithms.parallel.overloads]
                                           BidirectionalIterator first,
                                           BidirectionalIterator last,
                                           Predicate pred);

  namespace ranges {
    template<bidirectional_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      requires permutable<I>
      constexpr subrange<I> stable_partition(I first, S last, Pred pred, Proj proj = {});
    template<bidirectional_range R, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires permutable<iterator_t<R>>
      constexpr borrowed_subrange_t<R> stable_partition(R&& r, Pred pred, Proj proj = {});
  }

  template<class InputIterator, class OutputIterator1,
           class OutputIterator2, class Predicate>
    constexpr pair<OutputIterator1, OutputIterator2>
      partition_copy(InputIterator first, InputIterator last,
                     OutputIterator1 out_true, OutputIterator2 out_false,
                     Predicate pred);
  template<class ExecutionPolicy, class ForwardIterator, class ForwardIterator1,
           class ForwardIterator2, class Predicate>
    pair<ForwardIterator1, ForwardIterator2>
      partition_copy(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator first, ForwardIterator last,
                     ForwardIterator1 out_true, ForwardIterator2 out_false,
                     Predicate pred);

  namespace ranges {
    template<class I, class O1, class O2>
      using partition_copy_result = in_out_out_result<I, O1, O2>;

    template<input_iterator I, sentinel_for<I> S,
             weakly_incrementable O1, weakly_incrementable O2,
             class Proj = identity, indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_copyable<I, O1> && indirectly_copyable<I, O2>
      constexpr partition_copy_result<I, O1, O2>
        partition_copy(I first, S last, O1 out_true, O2 out_false, Pred pred,
                       Proj proj = {});
    template<input_range R, weakly_incrementable O1, weakly_incrementable O2,
             class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_copyable<iterator_t<R>, O1> &&
               indirectly_copyable<iterator_t<R>, O2>
      constexpr partition_copy_result<borrowed_iterator_t<R>, O1, O2>
        partition_copy(R&& r, O1 out_true, O2 out_false, Pred pred, Proj proj = {});
  }

  template<class ForwardIterator, class Predicate>
    constexpr ForwardIterator
      partition_point(ForwardIterator first, ForwardIterator last,
                      Predicate pred);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      constexpr I partition_point(I first, S last, Pred pred, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      constexpr borrowed_iterator_t<R>
        partition_point(R&& r, Pred pred, Proj proj = {});
  }

  // [alg.merge], merge
  template<class InputIterator1, class InputIterator2, class OutputIterator>
    constexpr OutputIterator
      merge(InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, InputIterator2 last2,
            OutputIterator result);
  template<class InputIterator1, class InputIterator2, class OutputIterator,
           class Compare>
    constexpr OutputIterator
      merge(InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, InputIterator2 last2,
            OutputIterator result, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator>
    ForwardIterator
      merge(ExecutionPolicy&& exec,                             // see [algorithms.parallel.overloads]
            ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2, ForwardIterator2 last2,
            ForwardIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator, class Compare>
    ForwardIterator
      merge(ExecutionPolicy&& exec,                             // see [algorithms.parallel.overloads]
            ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2, ForwardIterator2 last2,
            ForwardIterator result, Compare comp);

  namespace ranges {
    template<class I1, class I2, class O>
      using merge_result = in_in_out_result<I1, I2, O>;

    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             weakly_incrementable O, class Comp = ranges::less, class Proj1 = identity,
             class Proj2 = identity>
      requires mergeable<I1, I2, O, Comp, Proj1, Proj2>
      constexpr merge_result<I1, I2, O>
        merge(I1 first1, S1 last1, I2 first2, S2 last2, O result,
              Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, weakly_incrementable O, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires mergeable<iterator_t<R1>, iterator_t<R2>, O, Comp, Proj1, Proj2>
      constexpr merge_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>, O>
        merge(R1&& r1, R2&& r2, O result,
              Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class BidirectionalIterator>
    constexpr void inplace_merge(BidirectionalIterator first,
                                 BidirectionalIterator middle,
                                 BidirectionalIterator last);
  template<class BidirectionalIterator, class Compare>
    constexpr void inplace_merge(BidirectionalIterator first,
                                 BidirectionalIterator middle,
                                 BidirectionalIterator last, Compare comp);
  template<class ExecutionPolicy, class BidirectionalIterator>
    void inplace_merge(ExecutionPolicy&& exec,                  // see [algorithms.parallel.overloads]
                       BidirectionalIterator first,
                       BidirectionalIterator middle,
                       BidirectionalIterator last);
  template<class ExecutionPolicy, class BidirectionalIterator, class Compare>
    void inplace_merge(ExecutionPolicy&& exec,                  // see [algorithms.parallel.overloads]
                       BidirectionalIterator first,
                       BidirectionalIterator middle,
                       BidirectionalIterator last, Compare comp);

  namespace ranges {
    template<bidirectional_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I inplace_merge(I first, I middle, S last, Comp comp = {}, Proj proj = {});
    template<bidirectional_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        inplace_merge(R&& r, iterator_t<R> middle, Comp comp = {},
                      Proj proj = {});
  }

  // [alg.set.operations], set operations
  template<class InputIterator1, class InputIterator2>
    constexpr bool includes(InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2);
  template<class InputIterator1, class InputIterator2, class Compare>
    constexpr bool includes(InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2>
    bool includes(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first1, ForwardIterator1 last1,
                  ForwardIterator2 first2, ForwardIterator2 last2);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class Compare>
    bool includes(ExecutionPolicy&& exec,                       // see [algorithms.parallel.overloads]
                  ForwardIterator1 first1, ForwardIterator1 last1,
                  ForwardIterator2 first2, ForwardIterator2 last2,
                  Compare comp);

  namespace ranges {
    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             class Proj1 = identity, class Proj2 = identity,
             indirect_strict_weak_order<projected<I1, Proj1>, projected<I2, Proj2>> Comp =
               ranges::less>
      constexpr bool includes(I1 first1, S1 last1, I2 first2, S2 last2, Comp comp = {},
                              Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, class Proj1 = identity,
             class Proj2 = identity,
             indirect_strict_weak_order<projected<iterator_t<R1>, Proj1>,
                                        projected<iterator_t<R2>, Proj2>> Comp = ranges::less>
      constexpr bool includes(R1&& r1, R2&& r2, Comp comp = {},
                              Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class InputIterator1, class InputIterator2, class OutputIterator>
    constexpr OutputIterator
      set_union(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, InputIterator2 last2,
                OutputIterator result);
  template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    constexpr OutputIterator
                set_union(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, InputIterator2 last2,
                OutputIterator result, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator>
    ForwardIterator
      set_union(ExecutionPolicy&& exec,                         // see [algorithms.parallel.overloads]
                ForwardIterator1 first1, ForwardIterator1 last1,
                ForwardIterator2 first2, ForwardIterator2 last2,
                ForwardIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator, class Compare>
    ForwardIterator
      set_union(ExecutionPolicy&& exec,                         // see [algorithms.parallel.overloads]
                ForwardIterator1 first1, ForwardIterator1 last1,
                ForwardIterator2 first2, ForwardIterator2 last2,
                ForwardIterator result, Compare comp);

  namespace ranges {
    template<class I1, class I2, class O>
      using set_union_result = in_in_out_result<I1, I2, O>;

    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             weakly_incrementable O, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires mergeable<I1, I2, O, Comp, Proj1, Proj2>
      constexpr set_union_result<I1, I2, O>
        set_union(I1 first1, S1 last1, I2 first2, S2 last2, O result, Comp comp = {},
                  Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, weakly_incrementable O,
             class Comp = ranges::less, class Proj1 = identity, class Proj2 = identity>
      requires mergeable<iterator_t<R1>, iterator_t<R2>, O, Comp, Proj1, Proj2>
      constexpr set_union_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>, O>
        set_union(R1&& r1, R2&& r2, O result, Comp comp = {},
                  Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class InputIterator1, class InputIterator2, class OutputIterator>
    constexpr OutputIterator
      set_intersection(InputIterator1 first1, InputIterator1 last1,
                       InputIterator2 first2, InputIterator2 last2,
                       OutputIterator result);
  template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    constexpr OutputIterator
      set_intersection(InputIterator1 first1, InputIterator1 last1,
                       InputIterator2 first2, InputIterator2 last2,
                       OutputIterator result, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator>
    ForwardIterator
      set_intersection(ExecutionPolicy&& exec,                  // see [algorithms.parallel.overloads]
                       ForwardIterator1 first1, ForwardIterator1 last1,
                       ForwardIterator2 first2, ForwardIterator2 last2,
                       ForwardIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator, class Compare>
    ForwardIterator
      set_intersection(ExecutionPolicy&& exec,                  // see [algorithms.parallel.overloads]
                       ForwardIterator1 first1, ForwardIterator1 last1,
                       ForwardIterator2 first2, ForwardIterator2 last2,
                       ForwardIterator result, Compare comp);

  namespace ranges {
    template<class I1, class I2, class O>
      using set_intersection_result = in_in_out_result<I1, I2, O>;

    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             weakly_incrementable O, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires mergeable<I1, I2, O, Comp, Proj1, Proj2>
      constexpr set_intersection_result<I1, I2, O>
        set_intersection(I1 first1, S1 last1, I2 first2, S2 last2, O result,
                         Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, weakly_incrementable O,
             class Comp = ranges::less, class Proj1 = identity, class Proj2 = identity>
      requires mergeable<iterator_t<R1>, iterator_t<R2>, O, Comp, Proj1, Proj2>
      constexpr set_intersection_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>, O>
        set_intersection(R1&& r1, R2&& r2, O result,
                         Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class InputIterator1, class InputIterator2, class OutputIterator>
    constexpr OutputIterator
      set_difference(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result);
  template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    constexpr OutputIterator
      set_difference(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator>
    ForwardIterator
      set_difference(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator1 first1, ForwardIterator1 last1,
                     ForwardIterator2 first2, ForwardIterator2 last2,
                     ForwardIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator, class Compare>
    ForwardIterator
      set_difference(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator1 first1, ForwardIterator1 last1,
                     ForwardIterator2 first2, ForwardIterator2 last2,
                     ForwardIterator result, Compare comp);

  namespace ranges {
    template<class I, class O>
      using set_difference_result = in_out_result<I, O>;

    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             weakly_incrementable O, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires mergeable<I1, I2, O, Comp, Proj1, Proj2>
      constexpr set_difference_result<I1, O>
        set_difference(I1 first1, S1 last1, I2 first2, S2 last2, O result,
                       Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, weakly_incrementable O,
             class Comp = ranges::less, class Proj1 = identity, class Proj2 = identity>
      requires mergeable<iterator_t<R1>, iterator_t<R2>, O, Comp, Proj1, Proj2>
      constexpr set_difference_result<borrowed_iterator_t<R1>, O>
        set_difference(R1&& r1, R2&& r2, O result,
                       Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  template<class InputIterator1, class InputIterator2, class OutputIterator>
    constexpr OutputIterator
      set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2,
                               OutputIterator result);
  template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    constexpr OutputIterator
      set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2,
                               OutputIterator result, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator>
    ForwardIterator
      set_symmetric_difference(ExecutionPolicy&& exec,          // see [algorithms.parallel.overloads]
                               ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2,
                               ForwardIterator result);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class ForwardIterator, class Compare>
    ForwardIterator
      set_symmetric_difference(ExecutionPolicy&& exec,          // see [algorithms.parallel.overloads]
                               ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2,
                               ForwardIterator result, Compare comp);

  namespace ranges {
    template<class I1, class I2, class O>
      using set_symmetric_difference_result = in_in_out_result<I1, I2, O>;

    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             weakly_incrementable O, class Comp = ranges::less,
             class Proj1 = identity, class Proj2 = identity>
      requires mergeable<I1, I2, O, Comp, Proj1, Proj2>
      constexpr set_symmetric_difference_result<I1, I2, O>
        set_symmetric_difference(I1 first1, S1 last1, I2 first2, S2 last2, O result,
                                 Comp comp = {}, Proj1 proj1 = {},
                                 Proj2 proj2 = {});
    template<input_range R1, input_range R2, weakly_incrementable O,
             class Comp = ranges::less, class Proj1 = identity, class Proj2 = identity>
      requires mergeable<iterator_t<R1>, iterator_t<R2>, O, Comp, Proj1, Proj2>
      constexpr set_symmetric_difference_result<borrowed_iterator_t<R1>,
                                                borrowed_iterator_t<R2>, O>
        set_symmetric_difference(R1&& r1, R2&& r2, O result, Comp comp = {},
                                 Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  // [alg.heap.operations], heap operations
  template<class RandomAccessIterator>
    constexpr void push_heap(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void push_heap(RandomAccessIterator first, RandomAccessIterator last,
                             Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        push_heap(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        push_heap(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last,
                            Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        pop_heap(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        pop_heap(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last,
                             Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        make_heap(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        make_heap(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
                             Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr I
        sort_heap(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Comp = ranges::less, class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr borrowed_iterator_t<R>
        sort_heap(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr bool is_heap(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr bool is_heap(RandomAccessIterator first, RandomAccessIterator last,
                           Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    bool is_heap(ExecutionPolicy&& exec,                        // see [algorithms.parallel.overloads]
                 RandomAccessIterator first, RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    bool is_heap(ExecutionPolicy&& exec,                        // see [algorithms.parallel.overloads]
                 RandomAccessIterator first, RandomAccessIterator last,
                 Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr bool is_heap(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr bool is_heap(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class RandomAccessIterator>
    constexpr RandomAccessIterator
      is_heap_until(RandomAccessIterator first, RandomAccessIterator last);
  template<class RandomAccessIterator, class Compare>
    constexpr RandomAccessIterator
      is_heap_until(RandomAccessIterator first, RandomAccessIterator last,
                    Compare comp);
  template<class ExecutionPolicy, class RandomAccessIterator>
    RandomAccessIterator
      is_heap_until(ExecutionPolicy&& exec,                     // see [algorithms.parallel.overloads]
                    RandomAccessIterator first, RandomAccessIterator last);
  template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
    RandomAccessIterator
      is_heap_until(ExecutionPolicy&& exec,                     // see [algorithms.parallel.overloads]
                    RandomAccessIterator first, RandomAccessIterator last,
                    Compare comp);

  namespace ranges {
    template<random_access_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr I is_heap_until(I first, S last, Comp comp = {}, Proj proj = {});
    template<random_access_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr borrowed_iterator_t<R>
        is_heap_until(R&& r, Comp comp = {}, Proj proj = {});
  }

  // [alg.min.max], minimum and maximum
  template<class T> constexpr const T& min(const T& a, const T& b);
  template<class T, class Compare>
    constexpr const T& min(const T& a, const T& b, Compare comp);
  template<class T>
    constexpr T min(initializer_list<T> t);
  template<class T, class Compare>
    constexpr T min(initializer_list<T> t, Compare comp);

  namespace ranges {
    template<class T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr const T& min(const T& a, const T& b, Comp comp = {}, Proj proj = {});
    template<copyable T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr T min(initializer_list<T> r, Comp comp = {}, Proj proj = {});
    template<input_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      requires indirectly_copyable_storable<iterator_t<R>, range_value_t<R>*>
      constexpr range_value_t<R>
        min(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class T> constexpr const T& max(const T& a, const T& b);
  template<class T, class Compare>
    constexpr const T& max(const T& a, const T& b, Compare comp);
  template<class T>
    constexpr T max(initializer_list<T> t);
  template<class T, class Compare>
    constexpr T max(initializer_list<T> t, Compare comp);

  namespace ranges {
    template<class T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr const T& max(const T& a, const T& b, Comp comp = {}, Proj proj = {});
    template<copyable T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr T max(initializer_list<T> r, Comp comp = {}, Proj proj = {});
    template<input_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      requires indirectly_copyable_storable<iterator_t<R>, range_value_t<R>*>
      constexpr range_value_t<R>
        max(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class T> constexpr pair<const T&, const T&> minmax(const T& a, const T& b);
  template<class T, class Compare>
    constexpr pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp);
  template<class T>
    constexpr pair<T, T> minmax(initializer_list<T> t);
  template<class T, class Compare>
    constexpr pair<T, T> minmax(initializer_list<T> t, Compare comp);

  namespace ranges {
    template<class T>
      using minmax_result = min_max_result<T>;

    template<class T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr minmax_result<const T&>
        minmax(const T& a, const T& b, Comp comp = {}, Proj proj = {});
    template<copyable T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr minmax_result<T>
        minmax(initializer_list<T> r, Comp comp = {}, Proj proj = {});
    template<input_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      requires indirectly_copyable_storable<iterator_t<R>, range_value_t<R>*>
      constexpr minmax_result<range_value_t<R>>
        minmax(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator>
    constexpr ForwardIterator min_element(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class Compare>
    constexpr ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
                                          Compare comp);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator min_element(ExecutionPolicy&& exec,         // see [algorithms.parallel.overloads]
                                ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class Compare>
    ForwardIterator min_element(ExecutionPolicy&& exec,         // see [algorithms.parallel.overloads]
                                ForwardIterator first, ForwardIterator last,
                                Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr I min_element(I first, S last, Comp comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr borrowed_iterator_t<R>
        min_element(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator>
    constexpr ForwardIterator max_element(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class Compare>
    constexpr ForwardIterator max_element(ForwardIterator first, ForwardIterator last,
                                          Compare comp);
  template<class ExecutionPolicy, class ForwardIterator>
    ForwardIterator max_element(ExecutionPolicy&& exec,         // see [algorithms.parallel.overloads]
                                ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class Compare>
    ForwardIterator max_element(ExecutionPolicy&& exec,         // see [algorithms.parallel.overloads]
                                ForwardIterator first, ForwardIterator last,
                                Compare comp);

  namespace ranges {
    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr I max_element(I first, S last, Comp comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr borrowed_iterator_t<R>
        max_element(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class ForwardIterator>
    constexpr pair<ForwardIterator, ForwardIterator>
      minmax_element(ForwardIterator first, ForwardIterator last);
  template<class ForwardIterator, class Compare>
    constexpr pair<ForwardIterator, ForwardIterator>
      minmax_element(ForwardIterator first, ForwardIterator last, Compare comp);
  template<class ExecutionPolicy, class ForwardIterator>
    pair<ForwardIterator, ForwardIterator>
      minmax_element(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator first, ForwardIterator last);
  template<class ExecutionPolicy, class ForwardIterator, class Compare>
    pair<ForwardIterator, ForwardIterator>
      minmax_element(ExecutionPolicy&& exec,                    // see [algorithms.parallel.overloads]
                     ForwardIterator first, ForwardIterator last, Compare comp);

  namespace ranges {
    template<class I>
      using minmax_element_result = min_max_result<I>;

    template<forward_iterator I, sentinel_for<I> S, class Proj = identity,
             indirect_strict_weak_order<projected<I, Proj>> Comp = ranges::less>
      constexpr minmax_element_result<I>
        minmax_element(I first, S last, Comp comp = {}, Proj proj = {});
    template<forward_range R, class Proj = identity,
             indirect_strict_weak_order<projected<iterator_t<R>, Proj>> Comp = ranges::less>
      constexpr minmax_element_result<borrowed_iterator_t<R>>
        minmax_element(R&& r, Comp comp = {}, Proj proj = {});
  }

  // [alg.clamp], bounded value
  template<class T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi);
  template<class T, class Compare>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp);

  namespace ranges {
    template<class T, class Proj = identity,
             indirect_strict_weak_order<projected<const T*, Proj>> Comp = ranges::less>
      constexpr const T&
        clamp(const T& v, const T& lo, const T& hi, Comp comp = {}, Proj proj = {});
  }

  // [alg.lex.comparison], lexicographical comparison
  template<class InputIterator1, class InputIterator2>
    constexpr bool
      lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2);
  template<class InputIterator1, class InputIterator2, class Compare>
    constexpr bool
      lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2,
                              Compare comp);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2>
    bool
      lexicographical_compare(ExecutionPolicy&& exec,           // see [algorithms.parallel.overloads]
                              ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2);
  template<class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2,
           class Compare>
    bool
      lexicographical_compare(ExecutionPolicy&& exec,           // see [algorithms.parallel.overloads]
                              ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2,
                              Compare comp);

  namespace ranges {
    template<input_iterator I1, sentinel_for<I1> S1, input_iterator I2, sentinel_for<I2> S2,
             class Proj1 = identity, class Proj2 = identity,
             indirect_strict_weak_order<projected<I1, Proj1>, projected<I2, Proj2>> Comp =
               ranges::less>
      constexpr bool
        lexicographical_compare(I1 first1, S1 last1, I2 first2, S2 last2,
                                Comp comp = {}, Proj1 proj1 = {}, Proj2 proj2 = {});
    template<input_range R1, input_range R2, class Proj1 = identity,
             class Proj2 = identity,
             indirect_strict_weak_order<projected<iterator_t<R1>, Proj1>,
                                        projected<iterator_t<R2>, Proj2>> Comp = ranges::less>
      constexpr bool
        lexicographical_compare(R1&& r1, R2&& r2, Comp comp = {},
                                Proj1 proj1 = {}, Proj2 proj2 = {});
  }

  // [alg.three.way], three-way comparison algorithms
  template<class InputIterator1, class InputIterator2, class Cmp>
    constexpr auto
      lexicographical_compare_three_way(InputIterator1 b1, InputIterator1 e1,
                                        InputIterator2 b2, InputIterator2 e2,
                                        Cmp comp)
        -> decltype(comp(*b1, *b2));
  template<class InputIterator1, class InputIterator2>
    constexpr auto
      lexicographical_compare_three_way(InputIterator1 b1, InputIterator1 e1,
                                        InputIterator2 b2, InputIterator2 e2);

  // [alg.permutation.generators], permutations
  template<class BidirectionalIterator>
    constexpr bool next_permutation(BidirectionalIterator first,
                                    BidirectionalIterator last);
  template<class BidirectionalIterator, class Compare>
    constexpr bool next_permutation(BidirectionalIterator first,
                                    BidirectionalIterator last, Compare comp);

  namespace ranges {
    template<class I>
      using next_permutation_result = in_found_result<I>;

    template<bidirectional_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr next_permutation_result<I>
        next_permutation(I first, S last, Comp comp = {}, Proj proj = {});
    template<bidirectional_range R, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr next_permutation_result<borrowed_iterator_t<R>>
        next_permutation(R&& r, Comp comp = {}, Proj proj = {});
  }

  template<class BidirectionalIterator>
    constexpr bool prev_permutation(BidirectionalIterator first,
                                    BidirectionalIterator last);
  template<class BidirectionalIterator, class Compare>
    constexpr bool prev_permutation(BidirectionalIterator first,
                                    BidirectionalIterator last, Compare comp);

  namespace ranges {
    template<class I>
      using prev_permutation_result = in_found_result<I>;

    template<bidirectional_iterator I, sentinel_for<I> S, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<I, Comp, Proj>
      constexpr prev_permutation_result<I>
        prev_permutation(I first, S last, Comp comp = {}, Proj proj = {});
    template<bidirectional_range R, class Comp = ranges::less,
             class Proj = identity>
      requires sortable<iterator_t<R>, Comp, Proj>
      constexpr prev_permutation_result<borrowed_iterator_t<R>>
        prev_permutation(R&& r, Comp comp = {}, Proj proj = {});
  }
}
*/
