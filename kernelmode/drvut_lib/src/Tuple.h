#pragma once

#include "Utility.h"

namespace drvut {
namespace internal {

template <typename... Ts>
class Tuple {};

template <typename T, typename... Ts>
class Tuple<T, Ts...> : public Tuple<Ts...> {
public:
    Tuple(T t, Ts... ts) : Tuple<Ts...>(ts...), tail(t) {
        // left blnk intentionally
    }

    T tail;
    static constexpr size_t size = sizeof...(Ts) + 1;
};

class TupleUtils final {
public:
    TupleUtils() = delete;

    template <size_t index, typename T, typename... Ts>
    static auto& get(Tuple<T, Ts...>& t) {
        static_assert(index < sizeof...(Ts) + 1, "index out of bound");

        if constexpr (index > 0) {
            return get<index - 1, Ts...>(static_cast<Tuple<Ts...>&>(t));
        } else {
            return t.tail;
        }
    }

    template <typename T, typename... Ts>
    static size_t sizeOf(Tuple<T, Ts...>& t) {
        return sizeof...(Ts) + 1;
    }

private:
    template <typename F, typename TupleType, size_t... INDEXES>
    static decltype(auto) applyImpl(F&& f, TupleType t, std::index_sequence<INDEXES...>) {
        return f(get<INDEXES>(t)...);
    }

public:
    template <typename F, typename TupleType>
    static decltype(auto) apply(F&& f, TupleType t) {
        return applyImpl(f, std::move(t), std::make_index_sequence<TupleType::size>());
    }
};

}
}
