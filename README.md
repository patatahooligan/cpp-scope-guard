# cpp-scope-guard

Just a small test project to play around with modern c++ constructs. It is based
on the classic concept of a scope guard: a function that runs when you exit
the current scope, usually to perform clean-up. But I want to enhance the
concept by adding scope guards that trigger only on succesful exit and only when
exceptions are thrown.

Don't use this. It's a toy project and highly experimental. There's no guarantee
that I will maintain it or make any effort not to break code that uses it. If it
turns out well, I'll remove this warning to show that it's more appropriate for
use.
