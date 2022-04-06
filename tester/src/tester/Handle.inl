#pragma once

#include "Handle.h"

#include "Exceptions.h"

template <typename T>
    requires HandleTraits<T>
Handle<T>::Handle(typename T::HandleType handle) : 
    m_handle(handle) {
    if (handle == T::INVALID_VALUE) {
        throw T::ExceptionType(L"Invalid handle value");
    }
}

template <typename T>
    requires HandleTraits<T>
Handle<T>::~Handle() {
    if (m_handle != T::INVALID_VALUE) {
        if (!T::close(m_handle)) {
            traceException(T::ExceptionType(L"Failed closing service handle"));
        }
    }
}

template <typename T>
    requires HandleTraits<T>
Handle<T>::Handle(Handle<T>&& other) noexcept : 
    m_handle(std::exchange(other.m_handle, T::INVALID_VALUE)) {
    // Left blank intentionally
}

template <typename T>
    requires HandleTraits<T>
Handle<T>& Handle<T>::operator=(Handle<T>&& other) noexcept {
    m_handle = std::exchange(other.m_handle, HandleTraits::INVALID_VALUE);
    return *this;
}

template <typename T>
    requires HandleTraits<T>
Handle<T>::operator typename T::HandleType() const {
    return m_handle;
}
