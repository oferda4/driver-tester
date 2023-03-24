#pragma once

#include "drvut/internal/Tuple.h"

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
    static size_t forEach(Tuple<Ts...>& t, F func, size_t maxIndex = sizeof...(Ts));

private:
    template <typename F, typename TupleType, size_t... INDEXES>
    static void applyImpl(F&& f, TupleType t, std::index_sequence<INDEXES...>);

public:
    template <typename F, typename TupleType>
    static void apply(F&& f, TupleType t);
};

}
}

#include "drvut/internal/TupleUtils.inl"
