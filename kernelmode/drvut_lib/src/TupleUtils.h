#pragma once

#include "Tuple.h"

namespace drvut {
namespace internal {

class TupleUtils final {
public:
    TupleUtils() = delete;

    template <size_t index, typename T, typename... Ts>
    static auto& get(Tuple<T, Ts...>& t);
    template <typename T, typename... Ts>
    static size_t sizeOf(Tuple<T, Ts...>& t);

    template <size_t index = 0, typename F, typename... Ts>
    static void forEach(Tuple<Ts...>& t, F func) {
        if constexpr (index < sizeof...(Ts)) {
            func(get<index>(t));
            forEach<index + 1, F, Ts...>(t, func);
        }
    }

private:
    template <typename F, typename TupleType, size_t... INDEXES>
    static void applyImpl(F&& f, TupleType t, std::index_sequence<INDEXES...>);

public:
    template <typename F, typename TupleType>
    static void apply(F&& f, TupleType t);
};

}
}

#include "TupleUtils.inl"
