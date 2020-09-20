#include "scope-guard.hpp"

#include <iostream>

int main()
{
    OnScopeExit on_scope_exit = []() {
        std::cout << "Exiting scope\n";
    };

    std::cout << "This should print first\n";
}
