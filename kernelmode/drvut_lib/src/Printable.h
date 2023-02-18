#pragma once

#include "Defs.h"
#include "Concepts.h"
#include "StringUtils.h"

namespace drvut {

template <typename T>
concept Printable = requires(const T& printable) {
    { printable.toString() } -> internal::std::same_as<String>;
};

template <internal::std::integral T>
class I final {
public:
    explicit I(T num);

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

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
class AreEqual final {
public:
    AreEqual(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
class AreNotEqual final {
public:
    AreNotEqual(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

}

#include "Printable.inl"
