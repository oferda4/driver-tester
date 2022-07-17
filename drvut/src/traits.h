#pragma once

namespace std {
template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const { return value; }
    constexpr value_type operator()() const { return value; }
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T, class U>
struct is_same : std::false_type {};

template <class T>
struct is_same<T, T> : std::true_type {};

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;
}
