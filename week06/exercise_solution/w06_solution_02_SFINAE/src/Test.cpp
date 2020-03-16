#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


enum class Result {
	Integer, Float, Other
};

struct S1{};
struct S2{};
struct S3{};


//Template Parameter SFINAE
//template <typename T, typename = std::enable_if_t<
//			std::negation_v<
//				std::disjunction<std::is_integral<T>, std::is_floating_point<T>>
//			>>>
//Result consume(T value, S1 = {}) {
//	return Result::Other;
//}
//
//template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
//Result consume(T value, S2 = {}) {
//	return Result::Float;
//}
//
//template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
//Result consume(T value, S3 = {}) {
//	return Result::Integer;
//}

//Return Type SFINAE
//template <typename T>
//std::enable_if_t<
//			std::negation_v<
//				std::disjunction<std::is_integral<T>, std::is_floating_point<T>>
//			>, Result> consume(T value, S1 = {}) {
//	return Result::Other;
//}
//
//template <typename T>
//std::enable_if_t<std::is_floating_point_v<T>, Result> consume(T value, S2 = {}) {
//	return Result::Float;
//}
//
//template <typename T>
//std::enable_if_t<std::is_integral_v<T>, Result> consume(T value, S3 = {}) {
//	return Result::Integer;
//}

//Function Parameter SFINAE
template <typename T>
Result consume(T value, std::enable_if_t<
		std::negation_v<
			std::disjunction<std::is_integral<T>, std::is_floating_point<T>>
		>, S1> = {}) {
	return Result::Other;
}

template <typename T>
Result consume(T value, std::enable_if_t<std::is_floating_point_v<T>, S2> = {}) {
	return Result::Float;
}

template <typename T>
Result consume(T value, std::enable_if_t<std::is_integral_v<T>, S3> = {}) {
	return Result::Integer;
}


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


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testConsumeWithIntArgumentsReturnInteger));
	s.push_back(CUTE(testConsumeWithOtherArgumentsReturnOther));
	s.push_back(CUTE(testConsumeWithFloatArgumentsReturnFloat));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
