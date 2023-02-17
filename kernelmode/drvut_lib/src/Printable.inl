#pragma once

#include "Printable.h"

namespace drvut {

template <internal::std::integral T>
I<T>::I(T num) : m_num(num) {
    // left blank itnentionally
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

}