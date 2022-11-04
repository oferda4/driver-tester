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
    if (m_data) {
        delete[] m_data;
    }
}

template <typename T>
Array<T>::Array(Array&& other) noexcept 
    : m_data(std::exchange(other.m_data, nullptr)),
      m_size(std::exchange(other.m_size, 0)) {
    // intentionally left blank
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        m_data = std::exchange(other.m_data, nullptr);
        m_size = std::exchange(other.m_size, 0);
    }
    return *this;
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