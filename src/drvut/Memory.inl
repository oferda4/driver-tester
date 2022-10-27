#pragma once

#include "Memory.h"

namespace drvut {
namespace internal {
namespace std {

template<typename T>
unique_ptr<T>::unique_ptr(T* ptr) : m_ptr(ptr) {
    // Left blank intentionally
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) : m_ptr(std::exchange(other.m_ptr, nullptr)) {
    // Left blank intentionally
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) {
    if (this == other) {
        return *this;
    }
    m_ptr = std::exchange(other.m_ptr, nullptr);
    return *this;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete m_ptr;
}

template <typename T>
T* unique_ptr<T>::operator->() {
    return m_ptr;
}

template <typename T>
const T* unique_ptr<T>::operator->() const {
    return m_ptr;
}

template <typename T>
T& unique_ptr<T>::operator*() {
    return *m_ptr;
}

template <typename T>
const T& unique_ptr<T>::operator*() const {
    return m_ptr;
}

template <typename T>
bool unique_ptr<T>::operator==(decltype(nullptr)) const {
    return m_ptr == nullptr;
}

}
}
}