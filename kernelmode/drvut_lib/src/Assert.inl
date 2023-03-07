#pragma once

#include "StringUtils.h"
#include "Printable.h"
#include "Error.h"

namespace drvut {

template <typename T>
void assert(const T& cond) {
    static_assert(internal::std::is_convertible_v<T, bool>, "you should assert things that can be convertible to bool");
    if (!static_cast<bool>(cond)) {
        ErrorMessage::append(
            StringUtils::concat("assertion: ", PrintableUtils::printableOrUnknown(cond)));
    }
}

}
