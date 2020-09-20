#pragma once

#include <concepts>

template<std::invocable CallableType>
class OnScopeExit {
    public:
        void release() const noexcept
        {
            active = false;
        }

        OnScopeExit(CallableType exit_function):
            exit_function(exit_function) {}

        ~OnScopeExit()
        {
            if (active)
                exit_function();
        }

    private:
        bool active = true;
        CallableType exit_function;
};
