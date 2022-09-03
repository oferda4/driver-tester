#pragma once

#include "Array.h"
#include "Defs.h"

namespace drvut {
namespace internal {

template<typename T>
Array<T>::Array(size_t count) : m_data(new T[count]), m_count(count) {
    // Left blank intentionally
}

template <typename T>
Array<T>::~Array() {
    delete[] m_data;
}

template <typename T>
size_t Array<T>::count() {
    return m_count;
}

template <typename T>
T& Array<T>::at(size_t index) {
    if (index >= m_count) {
        ExRaiseStatus(STATUS_ACCESS_VIOLATION);
    }
    return m_data[index];
}

}
}