# Perfect Forwarding

***Question:*** We have an overload of the `push` member function with a parameter of type `T&&`. Why is `T&&` always an rvalue reference (and not a forwarding reference)?

***Answer:*** `T` is not in a deduced context for the `push` member function. Because the surrounding `BoundedBuffer` template already associates the element type to `T` upon instanciation, it cannot be suddenly replaced by another type depending on the context of the `push` call. It would be different if push was a member function template itself:
```cpp
  template <typename ArgType>
  void push(ArgType &&) {
    ...
  }
```