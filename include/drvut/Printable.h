#pragma once

#include "drvut/Defs.h"
#include "drvut/internal/Concepts.h"
#include "drvut/internal/StringUtils.h"

namespace drvut {

template <typename T>
concept Printable = requires(const T& printable) {
    { printable.toString() } -> internal::std::same_as<String>;
};

class PrintableUtils final {
public:
    PrintableUtils() = delete;

    template <typename T>
    static String printableOrUnknown(const T& obj);
};

template <internal::std::integral T>
class I final {
public:
    explicit I(T num);

    operator T() const;
    T get() const;
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

template <typename T, typename U>
    requires(internal::std::greater_comparable<T, U>)
class Greater final {
public:
    Greater(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

template <typename T, typename U>
    requires(internal::std::greater_or_equal_comparable<T, U>)
class GreaterOrEqual final {
public:
    GreaterOrEqual(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

template <typename T, typename U>
    requires(internal::std::lower_comparable<T, U>)
class Lower final {
public:
    Lower(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

template <typename T, typename U>
    requires(internal::std::lower_or_equal_comparable<T, U>)
class LowerOrEqual final {
public:
    LowerOrEqual(T left, U right);

    operator bool() const;
    String toString() const;

public:
    T m_left;
    U m_right;
};

}

#include "drvut/Printable.inl"
