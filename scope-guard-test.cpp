#include "scope-guard.hpp"

#include <iostream>

auto move_scope_guard() {
    OnScopeExit on_scope_exit = []() {
        std::cout <<
            "This OnScopeExit was moved and should trigger when main exits\n";
    };
    return on_scope_exit;
}

int main()
{
    const OnScopeExit on_scope_exit = []() {
        std::cout << "This should trigger last when main exits\n";
    };

    const auto moved_scope_exit = move_scope_guard();

    std::cout << "Main is about to exit\n";
}
