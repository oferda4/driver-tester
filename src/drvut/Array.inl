#pragma once

#include "Array.h"
#include "Defs.h"

namespace drvut {
namespace internal {

template<typename T>
Array<T>::Array(size_t size) : m_data(new T[size]), m_size(size) {
    // Left blank intentionally
}

template <typename T>
Array<T>::~Array() {
    delete[] m_data;
}

template <typename T>
size_t Array<T>::size() const {
    return m_size;
}

template <typename T>
T& Array<T>::at(size_t index) {
    return const_cast<T&>(static_cast<const Array<T>*>(this)->at(index));
}

template <typename T>
const T& Array<T>::at(size_t index) const {
    if (index >= m_size) {
        ExRaiseStatus(STATUS_ACCESS_VIOLATION);
    }
    return m_data[index];
}

}
}