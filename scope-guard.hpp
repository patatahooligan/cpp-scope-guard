#pragma once

#include <concepts>
#include <exception>
#include <type_traits>
#include <utility>

template<std::invocable CallableType>
class OnScopeExit {
    public:
        void release() const noexcept
        {
            active = false;
        }

        OnScopeExit(CallableType exit_function)
            noexcept(std::is_move_constructible<CallableType>::value):
                exit_function(std::move(exit_function)) {}

        OnScopeExit(OnScopeExit &&other)
            noexcept(std::is_move_constructible<CallableType>::value):
                exit_function(std::move(other.exit_function))
        {
            other.active = false;
        }

        // Defining the above constructors should prevent the implicit
        // declaration of these, but I let's show intent by explicitly
        // forbidding them
        OnScopeExit() = delete;
        OnScopeExit(const OnScopeExit&) = delete;

        ~OnScopeExit()
            noexcept(std::is_nothrow_invocable<CallableType>::value)
        {
            if (active)
                exit_function();
        }

    protected:
        bool active = true;
        CallableType exit_function;
};

template<std::invocable CallableType>
class OnScopeSuccess: OnScopeExit<CallableType> {
    public:
        OnScopeSuccess(CallableType exit_function):
            OnScopeExit<CallableType>(std::move(exit_function)) {}

        ~OnScopeSuccess() noexcept
        {
            if (std::uncaught_exceptions() > 0)
                this->active = false;
        }
};
