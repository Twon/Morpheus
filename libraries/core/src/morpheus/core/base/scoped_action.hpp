#pragma once

#include <concepts>
#include <utility>

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

template<typename T> 
class HoldReturnType;

template<>
class HoldReturnType<void> {};

template<typename T>
class HoldReturnType
{
public:

#if (__cpp_explicit_this_parameter >= 202110L)
    template<typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> value(this Self&& self) { return mEntryReturnValue; }
#else
    [[nodiscard]] auto& value() & { return mEntryReturnValue; }
    [[nodiscard]] auto const& value() const & { return mEntryReturnValue; }
    [[nodiscard]] auto&& value() && { return std::move(mEntryReturnValue); }
    [[nodiscard]] auto const&& value() const && { return  std::move(mEntryReturnValue); }
#endif

protected:
    T mEntryReturnValue;
};

}

template<std::invocable EntryAction, std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction;

template<std::invocable EntryAction, std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction : public detail::HoldReturnType< std::invoke_result_t<EntryAction> >
{
public:
    constexpr ScopedAction(EntryAction onEntry, ExitAction onExit)
    :   mAction(std::move(onExit))
    {
        if constexpr (std::is_same_v<std::invoke_result_t<EntryAction>, void>)
            onEntry();
        else
            this->mEntryReturnValue = onEntry();
    }

    constexpr ScopedAction(ScopedAction const&) = delete;
    constexpr ScopedAction(ScopedAction&&) = delete;

    constexpr ScopedAction operator=(ScopedAction const&) = delete;
    constexpr ScopedAction operator=(ScopedAction&&) = delete;

    constexpr ~ScopedAction()
    {
        mAction();
    }

private:
    ExitAction mAction;
};


}