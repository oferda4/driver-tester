#pragma once

#include "StringUtils.h"

namespace drvut {
namespace internal {

template <size_t N>
String::String(char const (&data)[N]) : String(N - 1) {
    static_assert(N > 0, "string must at least contain null terminator");
    memcpy(m_data, data, N);
}

}
}