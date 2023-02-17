#pragma once

#include "String.h"

namespace drvut {
namespace internal {

template <size_t N>
String::String(char data[N]) : m_data(new char[N]), m_len(N) {
    memcpy(m_data, data, N);
}

}
}