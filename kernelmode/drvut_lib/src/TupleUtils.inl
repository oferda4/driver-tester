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

template <size_t index, typename F, typename... Ts>
size_t TupleUtils::forEach(Tuple<Ts...>& t, F func, size_t maxIndex) {
    if constexpr (index < sizeof...(Ts)) {
        if (index >= maxIndex) {
            return 0;
        }

        auto& input = get<index>(t);
        using FuncReturnType = decltype(std::declval<F>()(std::declval<decltype(input)>()));

        if constexpr (std::is_same_v<FuncReturnType, NTSTATUS>) {
            if (!NT_SUCCESS(func(input))) {
                return 0;
            }
        } else if constexpr (std::is_same_v<FuncReturnType, void>) {
            func(input);
        } else {
            []<bool flag = false>() {
                static_assert(flag, "you must use a function that return NTSTATUS or void");
            } ();
        }

        return 1 + forEach<index + 1, F, Ts...>(t, func, maxIndex);
    } else {
        return 0;
    }
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
