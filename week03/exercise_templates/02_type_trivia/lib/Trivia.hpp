#ifndef TRIVIA_HPP_
#define TRIVIA_HPP_

#include "Question.hpp"

#include <iosfwd>

#include <vector>

namespace TypeTrivia {

constexpr size_t const NUMBER_OF_QUESTIONS_TO_ASK = 10;

auto printAll(std::ostream& out, std::vector<Question> const& questions)
    -> void;
auto createRandomIndices(size_t to_exclusive) -> std::vector<size_t>;
auto pickQuestionsToAsk(std::vector<Question> const& questions)
    -> std::vector<Question>;
auto printAwesomeness(std::ostream& out,
                      unsigned correctAnswers,
                      unsigned numberOfQuestions) -> void;
auto trivia(std::ostream& out,
            std::istream& in,
            std::vector<Question> const& questions) -> void;

}  // namespace TypeTrivia

#endif /* TRIVIA_HPP_ */
