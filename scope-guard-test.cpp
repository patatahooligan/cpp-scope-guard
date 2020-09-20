#include "scope-guard.hpp"

#include <exception>
#include <iostream>

auto move_scope_guard() {
    OnScopeExit on_scope_exit = []() {
        std::cout <<
            "This OnScopeExit was moved and should trigger when main exits\n";
    };
    return on_scope_exit;
}

void throwing_function()
{
    OnScopeSuccess on_scope_success = []() {
        std::cout << "This should never print";
    };
    throw std::runtime_error("Dummy exception");
}

int main()
{
    const OnScopeExit on_scope_exit = []() {
        std::cout << "This should trigger last when main exits\n";
    };

    const auto moved_scope_exit = move_scope_guard();

    try {
        throwing_function();
    }
    catch(...)
    {
        // noop
    }

    std::cout << "Main is about to exit\n";
}
