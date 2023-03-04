#pragma once

#include "Tuple.h"

namespace drvut {
namespace internal {

template <typename T, typename... Ts>
template <typename>
Tuple<T, Ts...>::Tuple()
    : Tuple<Ts...>(), tail() {
    // left blank intentionally
}

template <typename T, typename... Ts>
Tuple<T, Ts...>::Tuple(T t, Ts... ts) : Tuple<Ts...>(ts...), tail(t) {
    // left blnk intentionally
}

}
}