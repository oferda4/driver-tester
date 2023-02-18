#pragma once

#include "Traits.h"

namespace drvut {
namespace internal {
namespace std {

namespace detail {
template <class T, class U>
concept SameHelper = std::is_same_v<T, U>;
}

template <class T, class U>
concept same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;

template <class T>
concept integral = 
    requires(T t, T* p, void (*f)(T)) { // T* parameter excludes reference types
    f(0);                   // Exclude enumeration types
    p + t;                  // Exclude everything not yet excluded but integral types
};

template <class T, class U>
concept equality_comparable =
    requires(const T& t, const U& u) {
        { t == u } -> std::same_as<bool>;
        { t != u } -> std::same_as<bool>;
        { u == t } -> std::same_as<bool>;
        { u != t } -> std::same_as<bool>;
};

template <class T, class U>
concept greater_comparable =
    requires(const T& t, const U& u) {
        { t > u } -> std::same_as<bool>;
};

template <class T, class U>
concept greater_or_equal_comparable =
    requires(const T& t, const U& u) {
        { t >= u } -> std::same_as<bool>;
};

template <class T, class U>
concept lower_comparable =
    requires(const T& t, const U& u) {
        { t < u } -> std::same_as<bool>;
};

template <class T, class U>
concept lower_or_equal_comparable =
    requires(const T& t, const U& u) {
        { t <= u } -> std::same_as<bool>;
};

}
}
}