#include "QuestionGenerator.hpp"
#include "Trivia.hpp"
#include <iostream>




auto main() -> int {
	auto questions = TypeTrivia::createQuestions();
	TypeTrivia::trivia(std::cout, std::cin, questions);
//	printAll(std::cout, questions);
}

