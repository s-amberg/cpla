/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2006-2018 Peter Sommerlad, IFS
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *********************************************************************************/

#ifndef CUTE_SUITE_H_
#define CUTE_SUITE_H_

#include "cute_test.h"

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>

namespace cute {

struct suite : std::vector<test> {
  using base = std::vector<test>;
  
  explicit suite(std::string suiteName = "Unnamed Suite", std::vector<test> tests = {}) : std::vector<test>(std::move(tests)), suiteName{std::move(suiteName)}{
  }

  // suite(std::string suiteName, std::initializer_list<test> tests) : base(tests), suiteName{std::move(suiteName)} {
  // }

  // template<typename InputIter>
  // suite(std::string suiteName, InputIter begin, InputIter end) : base(std::move(begin), std::move(end)), suiteName{std::move(suiteName)} {
  // }


  [[nodiscard]] auto SuiteName() const -> std::string { return suiteName; }

  auto SuiteName() -> std::string& { return suiteName; }

 private:
  std::string suiteName;
};

// convenience operator for appending to suites, might not be right
// deprecated, not supported by plug-in, not needed with Eclipse plug-in
inline auto operator+=(suite& left, suite const& right) -> suite& {
  left.insert(left.end(), right.begin(), right.end());
  return left;
}

inline auto operator+=(suite& left, test const& right) -> suite& {
  left.push_back(right);
  return left;
}

}  // namespace cute

#endif /*CUTE_SUITE_H_*/
