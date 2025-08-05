/// \file semaphore.hpp
///     Modularisation for https://eel.is/c++draft/semaphore.syn
export namespace std
{

#if (__cpp_lib_semaphore >= 201907L)

    // [thread.sema.cnt], class template counting_semaphore
    using std::counting_semaphore;

    using std::binary_semaphore;

#endif // #if (__cpp_lib_semaphore >= 201907L)

} // namespace std
