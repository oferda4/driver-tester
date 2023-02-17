#pragma once

#include "Printable.h"

namespace drvut {

namespace detail {
template <typename T>
String printableOrUnknown(const T& obj) {
    if constexpr (Printable<T>) {
        return obj.toString();
    } else {
        return String("unknown");
    }
}
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
    String result = detail::printableOrUnknown(m_left);
    result = internal::StringUtils::concat(result, " == ");
    result = internal::StringUtils::concat(result, detail::printableOrUnknown(m_left));
    return result;
}

}