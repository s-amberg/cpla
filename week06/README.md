# Exercises Week 6 - Advanced Templates
In these exercises you will modify your `BoundedBuffer` to always use heap memory for storing its elements and see the possible impact of overloading the `new` and `delete` operators when using the affected type in your code and in conjunction with the standard library.

# 1. Range Constructor for `BoundedBuffer`

You can add a range-constructor to your `BoundedBuffer` and add a deduction guide for it.

Signature of the range-constructor:
```cpp
template <typename Iter>
BoundedBuffer(Iter begin, Iter end);
```

**Note:** You don't need to include it in the testat.