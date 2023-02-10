#pragma once

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
};

}
}
