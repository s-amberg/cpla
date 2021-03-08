# Exercises Week 3 - Type Deduction

## Introductory Question
Question: We have an overload of the push member function with a parameter of type T&&. Why is T&& here always an rvalue reference (and not a forwarding reference)?

`void push(T&&)` is a member function of the `BoundedBuffer`template. The template parameter `T` belongs to the surrounding `BoundedBuffer` template and is not deduced in the context of the member function call `push`. Therefore, the parameter type `T&&` is an rvalue reference and *not* a forwarding reference here.

----


