/// \file stoptoken.hpp
///     Modularisation for https://eel.is/c++draft/thread.stoptoken.syn
export namespace std
{

// [stoptoken], class stop_token
using std::stop_token;

// [stopsource], class stop_source
using std::stop_source;

// no-shared-stop-state indicator
using std::nostopstate_t;
using std::nostopstate;

// [stopcallback], class template stop_callback
using std::stop_callback;

} // namespace std
