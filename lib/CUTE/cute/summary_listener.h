/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2007-2022 Peter Sommerlad, Thomas Corbat, IFS
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

#ifndef CUTE_SUMMARY_LISTENER_H_
#define CUTE_SUMMARY_LISTENER_H_

#include "counting_listener.h"
#include "cute_listener.h"
#include "cute_suite.h"

#include <iostream>

namespace cute {

template <typename Listener = cute::null_listener>
struct summary_listener : cute::counting_listener<Listener> {
  using Base = cute::counting_listener<Listener>;
  summary_listener(std::ostream &out = std::cout) : Base{}, out{out} {}
  ~summary_listener() {
    out << "\nSummary:\n";
    out << Base::numberOfTests << " test(s) run\n";
    out << Base::successfulTests << " test(s) passed\n";
    out << Base::failedTests << " test(s) failed\n";
    out << Base::errors << " test error(s)\n" << std::flush;
  }

private:
  std::ostream &out;
};

} // namespace cute
#endif /*CUTE_SUMMARY_LISTENER_H_*/
