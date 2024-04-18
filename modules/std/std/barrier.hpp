/// \file barrier.hpp
///     Modularisation for https://eel.is/c++draft/barrier.syn
export namespace std
{

#if (__cpp_lib_barrier >= 201907L)

    using std::barrier;

#endif // #if (__cpp_lib_barrier >= 201907L)

} // namespace std
