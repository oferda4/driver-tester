#pragma once

#include "Handle.h"

#include "Exceptions.h"

template <typename HandleTraits>
Handle<HandleTraits>::Handle(typename HandleTraits::Type handle) : m_handle(handle) {
    if (handle == ServiceHandleTraits::INVALID_VALUE) {
        throw WinAPIException(L"Invalid handle value");
    }
}

template <typename HandleTraits>
Handle<HandleTraits>::~Handle() {
    if (m_handle != ServiceHandleTraits::INVALID_VALUE) {
        ServiceHandleTraits::close(m_handle);
    }
}

template <typename HandleTraits>
Handle<HandleTraits>::Handle(Handle<HandleTraits>&& other) noexcept : m_handle(std::exchange(other.m_handle, HandleTraits::INVALID_VALUE)) {
    // Left blank intentionally
}

template <typename HandleTraits>
Handle<HandleTraits>& Handle<HandleTraits>::operator=(Handle<HandleTraits>&& other) noexcept {
    m_handle = std::exchange(other.m_handle, HandleTraits::INVALID_VALUE);
    return *this;
}

template <typename HandleTraits>
Handle<HandleTraits>::operator typename HandleTraits::Type() const {
    return m_handle;
}
