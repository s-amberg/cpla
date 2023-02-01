#include "Trivia.hpp"
#include "Question.hpp"

#include <algorithm>
#include <chrono>
#include <istream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace TypeTrivia {

auto printAll(std::ostream& out, std::vector<Question> const& questions)
    -> void {
  for (auto const& q : questions) {
    out << "Template Code: " << q.calledCode << '\n';
    out << "Calling Code: " << q.callingCode << '\n';
    out << "Type T: " << q.typeT << '\n';
    out << "Param Type: " << q.typeParamType << '\n';
    out << "---" << '\n';
  }
}

template <typename RNG_T>
auto createRandomIndices(size_t to_exclusive, RNG_T&& rng)
    -> std::vector<size_t> {
  std::vector<size_t> indices{};
  indices.resize(to_exclusive);
  std::iota(std::begin(indices), std::end(indices), 0);
  std::shuffle(std::begin(indices), std::end(indices),
               std::forward<RNG_T>(rng));
  return indices;
}

template <typename RNG_T>
auto pickQuestionsToAsk(std::vector<Question> const& questions, RNG_T&& rng)
    -> std::vector<Question> {
  auto numberOfQuestions =
      std::min(questions.size(), NUMBER_OF_QUESTIONS_TO_ASK);
  std::vector<Question> questionsToAsk{};
  auto indices =
      createRandomIndices(numberOfQuestions, std::forward<RNG_T>(rng));
  for (auto const& i : indices) {
    questionsToAsk.push_back(questions[i]);
  }
  return questionsToAsk;
}

auto printAwesomeness(std::ostream& out,
                      unsigned correctAnswers,
                      unsigned numberOfQuestions) -> void {
  if (numberOfQuestions == 0) {
    out << "You did not have much to do, did you?" << std::endl;
    return;
  }
  double successRate{correctAnswers * 100.0 / numberOfQuestions};
  out << "Your success rate was " << successRate << "%. ";
  if (successRate < 50.0) {
    out << "You should practice a little more." << std::endl;
  } else if (successRate < 75.0) {
    out << "That should almost be enough to pass the exam. If you are as lucky "
           "as this time.";
  } else if (successRate < 90.0) {
    out << "Keep practicing you are almost there.";
  } else if (successRate < 100.0) {
    out << "Oh, that was very close to perfect.";
  } else {
    out << "You are so awesome!";
  }
}

auto trivia(std::ostream& out,
            std::istream& in,
            std::vector<Question> const& questions) -> void {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng{seed};
  auto questionsToAsk = pickQuestionsToAsk(questions, rng);
  unsigned correctAnswers{0};
  auto numberOfQuestions = questionsToAsk.size() * 2;
  out << "I will ask you " << numberOfQuestions
      << " questions about type deduction cases. Good luck!\n\n";
  for (auto const& q : questionsToAsk) {
    out << "-----------------------------------------------------\n";
    out << "Consider the following function template declaration:\n";
    out << q.calledCode;
    out << "\n\n";
    out << "When calling this function with the following call:\n";
    out << q.callingCode;
    out << "\n\n";
    out << "What will be the type of T? " << std::flush;

    std::string answer_t{}, answer_p{};
    std::getline(in, answer_t);
    if (q.checkTypeT(answer_t)) {
      out << "Correct!\n\n";
      ++correctAnswers;
    } else {
      out << "Sorry, that's not correct. The correct answer is:\n";
      out << q.typeT;
      out << "\n\n";
    }
    out << "And what's the type of parameter t? " << std::flush;
    std::getline(in, answer_p);
    if (q.checkTypeP(answer_p)) {
      out << "Correct!\n\n";
      ++correctAnswers;
    } else {
      out << "Sorry, that's not correct. The correct answer is:\n";
      out << q.typeParamType;
      out << "\n\n";
    }
  }
  out << "That was the last question. You have " << correctAnswers << " out of "
      << numberOfQuestions << " correct!\n";
  printAwesomeness(out, correctAnswers, numberOfQuestions);
}

}  // namespace TypeTrivia