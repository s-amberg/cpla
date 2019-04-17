#ifndef FIBONACCI_H_
#define FIBONACCI_H_


inline constexpr unsigned long long fibo(unsigned n) {
	if (n < 2) {
		return n;
	}
	return fibo(n - 1) + fibo(n - 2);
}

template <unsigned long long n>
constexpr auto fibo_v = fibo(n);

inline constexpr unsigned long long operator"" _fibo(unsigned long long n) {
	return fibo(n);
}

#endif /* FIBONACCI_H_ */
