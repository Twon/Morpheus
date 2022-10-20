#pragma once

#include <concepts>
#include <utility>

namespace morpheus
{
template<std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction;

template<std::invocable ExitAction>
class [[nodiscard, maybe_unused]] ScopedAction
{
public:
    constexpr ScopedAction(ExitAction onExit, std::invocable auto initial)
    :   mAction(std::move(onExit))
    {
        initial();
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