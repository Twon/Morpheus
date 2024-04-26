#pragma once

//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#else
    #include <concepts>
    #include <utility>
//#endif // #if (MORPHEUS_MODULES_SUPPORT)


namespace morpheus
{
/*
template<std::invocable ExitAction, typename EntryAction>
class [[nodiscard, maybe_unused]] ScopedAction;

template<std::invocable ExitAction, typename EntryReturn, class... EntryArgTypes>
class [[nodiscard, maybe_unused]] ScopedAction<ExitAction, EntryReturn(EntryArgTypes...)>
{
public:
    constexpr ScopedAction(ExitAction onExit, std::invocable<EntryReturn(EntryArgTypes...)> auto initial)
    :   mAction(std::move(onExit))
    {
        initial();
    }
*/
namespace detail
{

template <typename T>
class HoldReturnType;

/// \class HoldReturnType<void>
///     Specialisation for entry action with a void return type.
template <>
class HoldReturnType<void>
{};

/// \class HoldReturnType
///     Holding type to own the return value of an entry action to a scoped action.
template <typename T>
class HoldReturnType
{
public:
#if (__cpp_explicit_this_parameter >= 202110L)
    /// Access the returned value of the entry action on beginning of the managed scope.
    template <typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> value(this Self&& self)
    {
        return mEntryReturnValue;
    }
#else
    /// Access the returned value of the entry action on beginning of the managed scope.
    [[nodiscard]] auto& value() & { return mEntryReturnValue; }

    /// Access the returned value of the entry action on beginning of the managed scope.
    [[nodiscard]] auto const& value() const& { return mEntryReturnValue; }

    /// Access the returned value of the entry action on beginning of the managed scope.
    [[nodiscard]] auto&& value() && { return std::move(mEntryReturnValue); }

    /// Access the returned value of the entry action on beginning of the managed scope.
    [[nodiscard]] auto const&& value() const&& { return std::move(mEntryReturnValue); }
#endif

protected:
    T mEntryReturnValue; ///< The returned value of the entry action on beginning of the managed scope.
};

} // namespace detail

template <std::invocable EntryAction, std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction;

/// \class ScopedAction
///     Declares an action to be called at (optionally) the beginning and end of a scope.
/// \tparam EntryAction Action to be called on creation of the scoped action.
/// \tparam ExitAction Action to be called on exit of the scoped action.
template <std::invocable EntryAction, std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction : public detail::HoldReturnType<std::invoke_result_t<EntryAction>>
{
public:
    constexpr ScopedAction(EntryAction onEntry, ExitAction onExit) : mAction(std::move(onExit))
    {
        if constexpr (std::is_same_v<std::invoke_result_t<EntryAction>, void>)
            onEntry();
        else
            this->mEntryReturnValue = onEntry();
    }

    constexpr ScopedAction(ScopedAction const&) = delete;
    constexpr ScopedAction(ScopedAction &&) = delete;

    constexpr ScopedAction operator=(ScopedAction const&) = delete;
    constexpr ScopedAction operator=(ScopedAction&&) = delete;

    constexpr ~ScopedAction() { mAction(); }

private:
    ExitAction mAction;
};

} // namespace morpheus
