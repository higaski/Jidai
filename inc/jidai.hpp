/// Jidai
///
/// \file   jidai.hpp
/// \author Vincent Hamp
/// \date   24/11/2018

#pragma once

#include <algorithm>
#include <cstdint>
#include <ctime>

namespace jidai {

/// Compilation date and time
struct CompilationTime {
  uint8_t day;
  uint8_t month;
  uint16_t year;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

namespace detail {

/// Length of the null-terminated string str
///
/// \param  str Pointer to the null-terminated byte strings to compare
/// \return Length of the C string str
constexpr size_t strlen(char const* str) {
  size_t retval{};

  while (str[retval])
    ++retval;

  return retval;
}

/// Compares two null-terminated byte strings lexicographically
///
/// \param  lhs Pointer to the null-terminated byte strings to compare
/// \param  rhs Pointer to the null-terminated byte strings to compare
/// \return <0  Negative value if lhs appears before rhs in lexicographical
///             order.
/// \return 0   Zero if lhs and rhs compare equal.
/// \return >0  Positive value if lhs appears after rhs in lexicographical
///             order.
constexpr int32_t strcmp(char const* lhs, char const* rhs) {
  size_t min{std::min(strlen(lhs), strlen(rhs))};
  size_t retval{};

  for (; retval < min; ++retval) {
    if (!lhs[retval] || !rhs[retval])
      break;

    if (lhs[retval] != rhs[retval])
      return static_cast<uint8_t>(lhs[retval]) -
             static_cast<uint8_t>(rhs[retval]);
  }

  return 0;
}

/// Interprets an integer value in a byte string pointed to by str
///
/// \param str  Pointer to the null-terminated byte string to be interpreted
/// \return Integer value corresponding to the contents of str
constexpr int32_t atoi(char const* str) {
  while (*str == ' ')
    ++str;

  int32_t retval{0};
  int32_t sign{1};

  switch (*str) {
    case '-':
      ++str;
      sign = -1;
      break;

    case '+':
      ++str;
      break;
  }

  while (char c = *str++) {
    if (c < '0' || c > '9')
      return retval;

    retval = retval * 10 + c - '0';
  }

  if (retval < 0)
    return 0;

  return retval * sign;
}

}  // namespace detail

/// Get compilation date and time
///
/// \return CompilationTime
constexpr CompilationTime make_compilation_time() {
  CompilationTime time{};

  // Set year
  time.day = detail::atoi(__DATE__ + 3);

  // Set month
  if (detail::strcmp(__DATE__, "Jan") == 0)
    time.month = 1;
  else if (detail::strcmp(__DATE__, "Feb") == 0)
    time.month = 2;
  else if (detail::strcmp(__DATE__, "Mar") == 0)
    time.month = 3;
  else if (detail::strcmp(__DATE__, "Apr") == 0)
    time.month = 4;
  else if (detail::strcmp(__DATE__, "May") == 0)
    time.month = 5;
  else if (detail::strcmp(__DATE__, "Jun") == 0)
    time.month = 6;
  else if (detail::strcmp(__DATE__, "Jul") == 0)
    time.month = 7;
  else if (detail::strcmp(__DATE__, "Aug") == 0)
    time.month = 8;
  else if (detail::strcmp(__DATE__, "Sep") == 0)
    time.month = 9;
  else if (detail::strcmp(__DATE__, "Oct") == 0)
    time.month = 10;
  else if (detail::strcmp(__DATE__, "Nov") == 0)
    time.month = 11;
  else if (detail::strcmp(__DATE__, "Dec") == 0)
    time.month = 12;

  // Set year
  time.year = detail::atoi(__DATE__ + 6);

  // Set hour
  time.hour = detail::atoi(__TIME__);

  // Set minute
  time.minute = detail::atoi(__TIME__ + 3);

  // Set second
  time.second = detail::atoi(__TIME__ + 6);

  return time;
}

/// Convert compilation time to seconds
///
/// \param  time  Compilation time to convert
/// \return Compilation time in seconds
constexpr size_t compilation_time2seconds(CompilationTime const time) {
  auto const count_leap_years{[&time]() {
    size_t retval{time.year};
    if (time.month <= 2)
      --retval;
    return retval / 4 - retval / 100 + retval / 400;
  }};

  bool const is_leap_year{(!(time.year % 4) && (time.year % 100)) ||
                          !(time.year % 400)};

  size_t days{time.year * 365 + count_leap_years()};

  days += time.month > 1 ? 31 : 0;
  days += time.month > 2 ? is_leap_year ? 29 : 28 : 0;
  days += time.month > 3 ? 31 : 0;
  days += time.month > 4 ? 30 : 0;
  days += time.month > 5 ? 31 : 0;
  days += time.month > 6 ? 30 : 0;
  days += time.month > 7 ? 31 : 0;
  days += time.month > 8 ? 31 : 0;
  days += time.month > 9 ? 30 : 0;
  days += time.month > 10 ? 31 : 0;
  days += time.month > 11 ? 30 : 0;

  days += time.day;

  return days * 24 * 3600 + time.hour * 3600 + time.minute * 60 + time.second;
}

/// Default unix epoch (be careful that GCC and Clang both disagree with me and
/// use 01:00:00 as default)
inline constexpr CompilationTime default_epoch{
    .day = 1, .month = 1, .year = 1970};

/// Make unix compilation time
///
/// \tparam T     Return type
/// \tparam epoch Epoch to use
/// \return Unix compilation time since epoch
template<typename T = time_t>
constexpr T make_unix_compilation_time(
    CompilationTime const epoch = default_epoch) {
  return static_cast<T>(compilation_time2seconds(make_compilation_time()) -
                        compilation_time2seconds(epoch));
}

}  // namespace jidai