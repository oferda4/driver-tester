#pragma once

#include "drvut/internal/StringUtils.h"
#include "drvut/Printable.h"
#include "drvut/internal/Error.h"

namespace drvut {

template <typename T>
void assert(const T& cond) {
    static_assert(internal::std::disjunction_v<
                        internal::std::is_convertible<T, bool>, 
                        internal::std::is_same<T, bool>>, 
                  "you should assert things that can be converted to bool");
    if (!static_cast<bool>(cond)) {
        internal::ErrorMessage::append(
            internal::StringUtils::concat("assert: ", PrintableUtils::printableOrUnknown(cond)));
        ExRaiseStatus(STATUS_ASSERTION_FAILURE);
    }
}

}
