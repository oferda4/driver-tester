#pragma once

#include "drvut/Defs.h"

#include "drvut/internal/Traits.h"
#include "drvut/internal/Utility.h"

namespace drvut {
namespace internal {

template <typename... Ts>
class Tuple {
public:
    static constexpr size_t size = 0;
};

template <typename T, typename... Ts>
class Tuple<T, Ts...> : public Tuple<Ts...> {
public:
    template <typename = std::enable_if_t<
                            std::conjunction_v<
                                std::is_default_constructible<Tuple<Ts...>>, 
                                std::is_default_constructible<T>
            >>>
    Tuple();
    Tuple(T t, Ts... ts);

    using NonReferenceTuple = Tuple<std::remove_reference_t<T>, std::remove_reference_t<Ts>...>;

    T tail;
    static constexpr size_t size = sizeof...(Ts) + 1;
};

}
}

#include "drvut/internal/Tuple.inl"
