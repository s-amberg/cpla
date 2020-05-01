//
// detail/tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_TSS_PTR_HPP
#define ASIO_DETAIL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../../../../../third_party/asio/include/asio/detail/config.hpp"

#if !defined(ASIO_HAS_THREADS)
# include "../../../../../third_party/asio/include/asio/detail/null_tss_ptr.hpp"
#elif defined(ASIO_HAS_THREAD_KEYWORD_EXTENSION)
# include "../../../../../third_party/asio/include/asio/detail/keyword_tss_ptr.hpp"
#elif defined(ASIO_WINDOWS)
# include "../../../../../third_party/asio/include/asio/detail/win_tss_ptr.hpp"
#elif defined(ASIO_HAS_PTHREADS)
# include "../../../../../third_party/asio/include/asio/detail/posix_tss_ptr.hpp"
#else
# error Only Windows and POSIX are supported!
#endif

#include "../../../../../third_party/asio/include/asio/detail/push_options.hpp"

namespace asio {
namespace detail {

template <typename T>
class tss_ptr
#if !defined(ASIO_HAS_THREADS)
  : public null_tss_ptr<T>
#elif defined(ASIO_HAS_THREAD_KEYWORD_EXTENSION)
  : public keyword_tss_ptr<T>
#elif defined(ASIO_WINDOWS)
  : public win_tss_ptr<T>
#elif defined(ASIO_HAS_PTHREADS)
  : public posix_tss_ptr<T>
#endif
{
public:
  void operator=(T* value)
  {
#if !defined(ASIO_HAS_THREADS)
    null_tss_ptr<T>::operator=(value);
#elif defined(ASIO_HAS_THREAD_KEYWORD_EXTENSION)
    keyword_tss_ptr<T>::operator=(value);
#elif defined(ASIO_WINDOWS)
    win_tss_ptr<T>::operator=(value);
#elif defined(ASIO_HAS_PTHREADS)
    posix_tss_ptr<T>::operator=(value);
#endif
  }
};

} // namespace detail
} // namespace asio

#include "../../../../../third_party/asio/include/asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_TSS_PTR_HPP
