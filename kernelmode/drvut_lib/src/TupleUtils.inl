#pragma once

#include "TupleUtils.h"
#include "FunctionUtils.h"

namespace drvut {
namespace internal {

template <size_t index, typename T, typename... Ts>
auto& TupleUtils::get(Tuple<T, Ts...>& t) {
    static_assert(index < sizeof...(Ts) + 1, "index out of bound");

    if constexpr (index > 0) {
        return get<index - 1, Ts...>(static_cast<Tuple<Ts...>&>(t));
    } else {
        return t.tail;
    }
}

template <typename T, typename... Ts>
size_t TupleUtils::sizeOf(Tuple<T, Ts...>& t) {
    return sizeof...(Ts) + 1;
}

template <typename F, typename TupleType, size_t... INDEXES>
void TupleUtils::applyImpl(F&& f, TupleType t, std::index_sequence<INDEXES...>) {
    f(get<INDEXES>(t)...);
}

template <typename F, typename TupleType>
void TupleUtils::apply(F&& f, TupleType t) {
    applyImpl(f, std::move(t), std::make_index_sequence<TupleType::size>());
}

}
}
