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

    operator T() const;
    String toString() const;

private:
    T m_num;
};

class B final {
public:
    B(bool boolean);

    operator bool() const;
    String toString() const;

private:
    bool m_boolean;
};

}

#include "Printable.inl"
