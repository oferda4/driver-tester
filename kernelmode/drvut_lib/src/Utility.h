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

template <size_t... INDEXES> struct index_sequence {};

namespace impl {
template <size_t N, size_t... INDEXES>
struct make_index_sequence_impl : make_index_sequence_impl<N - 1, N - 1, INDEXES...> {};

template <size_t... INDEXES>
struct make_index_sequence_impl<0, INDEXES...> {
    using type = index_sequence<INDEXES...>;
};
}

template <size_t N>
using make_index_sequence = typename impl::make_index_sequence_impl<N>::type;

}

}
}
