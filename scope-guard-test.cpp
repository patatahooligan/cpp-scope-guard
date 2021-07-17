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
    OnScopeFailure on_scope_failure = []() {
        std::cout << "This function threw\n";
    };
    throw std::runtime_error("Dummy exception");
}

void successful_function()
{
    OnScopeSuccess on_scope_success = []() {
        std::cout << "This function exited successfully\n";
    };
    OnScopeFailure on_scope_failure = []() {
        std::cout << "This should never print\n";
    };
}

int main()
{
    const OnScopeExit on_scope_exit = []() {
        std::cout << "This should trigger last when main exits\n";
    };

    const auto moved_scope_exit = move_scope_guard();

    successful_function();
    std::cout << "\n";
    try {
        throwing_function();
    }
    catch(...)
    {
        // noop
    }
    std::cout << "\n";

    std::cout << "Main is about to exit\n";
}
