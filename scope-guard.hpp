#pragma once

#include <concepts>
#include <exception>
#include <utility>

template<std::invocable CallableType>
class OnScopeExit {
    public:
        void release() const noexcept
        {
            active = false;
        }

        OnScopeExit(CallableType exit_function):
            exit_function(std::move(exit_function)) {}

        OnScopeExit(OnScopeExit &&other)
        {
            exit_function = std::move(other.exit_function);
            other.active = false;
        }

        // Defining the above constructors should prevent the implicit
        // declaration of these, but I let's show intent by explicitly
        // forbidding them
        OnScopeExit() = delete;
        OnScopeExit(const OnScopeExit&) = delete;

        ~OnScopeExit()
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
            if (std::uncaught_exceptions > 0)
                this->active = false;
        }
};
