#pragma once

#include "Defs.h"
#include "Concepts.h"
#include "StringUtils.h"

namespace drvut {

template <typename T>
concept Pintable = requires(const T& printable) {
    { printable.toString() } -> internal::std::same_as<String>;
};

template <internal::std::integral T>
class I final {
public:
    I(T num);

    String toString() const;

private:
    T m_num;
};

}

#include "Printable.inl"
