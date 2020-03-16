#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


enum class Result {
	Integer, Float, Other
};


template <typename T>
Result consume(T value) {
	return Result::Other;
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
