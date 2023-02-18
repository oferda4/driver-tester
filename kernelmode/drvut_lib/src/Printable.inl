#pragma once

#include "Printable.h"

namespace drvut {

namespace detail {
template <typename T, typename U>
String printWithOperator(const T& left, const U& right, const String& op);
template <typename T>
String printableOrUnknown(const T& obj);
}

template <internal::std::integral T>
I<T>::I(T num) : m_num(num) {
    // left blank itnentionally
}

template <internal::std::integral T>
I<T>::operator T() const {
    return m_num;
}

template <internal::std::integral T>
String I<T>::toString() const {
    T num = m_num;
    String currNumPrintable = "";
    
    if (num == 0) {
        return String("0");
    }
    
    if (num < 0) {
        return internal::StringUtils::concat("-", I(-m_num).toString());
    }

    // positive
    while (num > 0) {
        uint8_t currDigit = num % 10;
        char currDigitAsString[2] = { '0' + currDigit, '\x00' };
        currNumPrintable = internal::StringUtils::concat(currDigitAsString, currNumPrintable);
        num /= 10;
    }

    return currNumPrintable;
}

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
AreEqual<T, U>::AreEqual(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
          requires(internal::std::equality_comparable<T, U>)
AreEqual<T, U>::operator bool() const {
    return m_left == m_right;
}

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
String AreEqual<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, "==");
}

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
AreNotEqual<T, U>::AreNotEqual(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
AreNotEqual<T, U>::operator bool() const {
    return m_left != m_right;
}

template <typename T, typename U>
    requires(internal::std::equality_comparable<T, U>)
String AreNotEqual<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, "!=");
}

template <typename T, typename U>
    requires(internal::std::greater_comparable<T, U>)
Greater<T, U>::Greater(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
    requires(internal::std::greater_comparable<T, U>)
Greater<T, U>::operator bool() const {
    return m_left > m_right;
}

template <typename T, typename U>
    requires(internal::std::greater_comparable<T, U>)
String Greater<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, ">");
}

template <typename T, typename U>
    requires(internal::std::greater_or_equal_comparable<T, U>)
GreaterOrEqual<T, U>::GreaterOrEqual(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
    requires(internal::std::greater_or_equal_comparable<T, U>)
GreaterOrEqual<T, U>::operator bool() const {
    return m_left >= m_right;
}

template <typename T, typename U>
    requires(internal::std::greater_or_equal_comparable<T, U>)
String GreaterOrEqual<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, ">=");
}

template <typename T, typename U>
    requires(internal::std::lower_comparable<T, U>)
Lower<T, U>::Lower(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
    requires(internal::std::lower_comparable<T, U>)
Lower<T, U>::operator bool() const {
    return m_left < m_right;
}

template <typename T, typename U>
    requires(internal::std::lower_comparable<T, U>)
String Lower<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, "<");
}

template <typename T, typename U>
    requires(internal::std::lower_or_equal_comparable<T, U>)
LowerOrEqual<T, U>::LowerOrEqual(T left, U right) : m_left(left), m_right(right) {
    // left blank intentionally
}

template <typename T, typename U>
    requires(internal::std::lower_or_equal_comparable<T, U>)
LowerOrEqual<T, U>::operator bool() const {
    return m_left <= m_right;
}

template <typename T, typename U>
    requires(internal::std::lower_or_equal_comparable<T, U>)
String LowerOrEqual<T, U>::toString() const {
    return detail::printWithOperator(m_left, m_right, "<=");
}

template <typename T, typename U>
String detail::printWithOperator(const T& left, const U& right, const String& op) {
    String result = detail::printableOrUnknown(left);
    result = internal::StringUtils::concat(result, " ");
    result = internal::StringUtils::concat(result, op);
    result = internal::StringUtils::concat(result, " ");
    result = internal::StringUtils::concat(result, detail::printableOrUnknown(right));
    return result;
}

template <typename T>
String detail::printableOrUnknown(const T& obj) {
    if constexpr (Printable<T>) {
        return obj.toString();
    } else {
        return String("unknown");
    }
}

}