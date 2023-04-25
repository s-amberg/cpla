#include <atomic>
#include <iostream>
#include <string>

struct SimpleType {
	int first;
	float second;
};

struct NonTrivialCCtor {
	NonTrivialCCtor(NonTrivialCCtor const&) {
		std::cout << "copied!\n";
	}
};

struct NonTrivialCAssignment {
	NonTrivialCAssignment& operator=(NonTrivialCCtor const&) {
		std::cout << "copy assigned!\n";
		return *this;
	}
};

struct NonTrivialMember {
	int first;
	std::string second;
};

int main() {
	std::atomic<SimpleType> works { };
//	std::atomic<NonTrivialCCtor> does_not_work1 { };
//	std::atomic<NonTrivialCAssignment> does_not_work2 { };
//	std::atomic<NonTrivialMember> does_not_work3 { };
}
