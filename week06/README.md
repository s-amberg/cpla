# Exercises Week 6 - Advanced Templates
In these exercises you will modify your `BoundedBuffer` to always use heap memory for storing its elements and see the possible impact of overloading the `new` and `delete` operators when using the affected type in your code and in conjunction with the standard library.

## 1. Range Constructor for `BoundedBuffer`

You can add a range-constructor to your `BoundedBuffer` and add a deduction guide for it.

Signature of the range-constructor:
```cpp
template <typename Iter>
BoundedBuffer(Iter begin, Iter end);
```

**Note:** You don't need to include it in the testat.

## 2. Substitution Failure Is Not An Error

In the given template project you have a few CUTE unit tests for the `consume` function template:

```cpp
enum class Result {
	Integer, Float, Other
};

void testConsumeWithIntArgumentsReturnInteger() {
	ASSERT_EQUAL(Result::Integer, consume(1));
	ASSERT_EQUAL(Result::Integer, consume(1l));
	ASSERT_EQUAL(Result::Integer, consume(1ll));
	ASSERT_EQUAL(Result::Integer, consume(1u));
	ASSERT_EQUAL(Result::Integer, consume(1ul));
	ASSERT_EQUAL(Result::Integer, consume(1ull));
}

void testConsumeWithFloatArgumentsReturnFloat() {
	ASSERT_EQUAL(Result::Float, consume(1.0f));
	ASSERT_EQUAL(Result::Float, consume(1.0));
	ASSERT_EQUAL(Result::Float, consume(1.0l));
}

void testConsumeWithOtherArgumentsReturnOther() {
	using namespace std::string_literals;
	ASSERT_EQUAL(Result::Other, consume("other"s));
	ASSERT_EQUAL(Result::Other, consume(std::vector<int>{1,2,3}));
	ASSERT_EQUAL(Result::Other, consume(std::istringstream{"other"}));
}

```

Your task is to implement the `consume` function template and get the test cases green. As you can see from the test cases the argument types are different in each unit test:
* Only integral arguments
* Only floating point arguments
* Arguments of other types

The initial implementation of `consume`:
```cpp
template <typename T>
Result consume(T value) {
	return Result::Other;
}
```

### 2a) Add Overloads

You first need to add two overloads for the `consume` function template. They should have the return value hardcoded to `Result::Integer` and `Result::Float`. You will encounter a problem: You cannot create overloads with identical signature, even if you SFINAE-disable them. There is a trick you can apply though: You can create empty dummy classes that are used as an additional parameter for each overload, which have a default argument assigned. 

```cpp
struct Dummy1 {
};

template <typename T>
Result consume(T value, Dummy1 = {}) {
	return Result::Integer;
}
```

### 2b) Apply SFINAE

After you have the overloads it is still mandatory that only a single one is viable for each call. That means you need to apply SFINAE to each overload. You can use the type traits from [CPP Reference](https://en.cppreference.com/w/cpp/header/type_traits). You most likely need:
* `std::enable_if`
* `std::negation`
* `std::disjunction`
* `std::is_integral`
* `std::is_floating_point`

**Note:** You also need to disable the inital `consume` implementation in case the argument has integral or floating type.

Try to apply SFINAE in the three different spots you have seen in the lecture.