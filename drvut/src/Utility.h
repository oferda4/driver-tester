#pragma once

#include "Traits.h"

namespace drvut {
namespace internal {

namespace std {

template <class T>
[[nodiscard]] constexpr remove_reference_t<T>&& move(T&& arg) noexcept {
    return static_cast<remove_reference_t<T>&&>(arg);
}

template <class T, class Other = T>
constexpr T exchange(T& val, Other&& newVal) noexcept(
    conjunction_v<is_nothrow_move_constructible<T>, is_nothrow_assignable<T&, Other>>) {
    // assign _New_val to _Val, return previous _Val
    T oldVal = static_cast<T&&>(val);
    val = static_cast<Other&&>(newVal);
    return oldVal;
}

}

}
}
