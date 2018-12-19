//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <cstring>

namespace td {

namespace detail {

template <class T>
class As {
 public:
  explicit As(void *ptr) : ptr_(ptr) {
  }

  As(const As &new_value) = delete;
  As &operator=(const As &) = delete;
  As(As &&) = default;
  As &operator=(As &&new_value) && {
    std::memcpy(ptr_, new_value.ptr_, sizeof(T));
    return *this;
  }
  ~As() = default;

  As &operator=(const T &new_value) && {
    std::memcpy(ptr_, &new_value, sizeof(T));
    return *this;
  }

  operator T() const {
    T res;
    std::memcpy(&res, ptr_, sizeof(T));
    return res;
  }

 private:
  void *ptr_;
};

template <class T>
class ConstAs {
 public:
  explicit ConstAs(const void *ptr) : ptr_(ptr) {
  }

  operator T() const {
    T res;
    std::memcpy(&res, ptr_, sizeof(T));
    return res;
  }

 private:
  const void *ptr_;
};

}  // namespace detail

template <class ToT, class FromT>
detail::As<ToT> as(FromT *from) {
  return detail::As<ToT>(from);
}

template <class ToT, class FromT>
const detail::ConstAs<ToT> as(const FromT *from) {
  return detail::ConstAs<ToT>(from);
}

}  // namespace td
