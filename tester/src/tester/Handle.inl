#pragma once

#include "Handle.h"

#include "Exceptions.h"

template <typename HandleTraitsType, typename TracerType>
    requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
Handle<HandleTraitsType, TracerType>::Handle(typename HandleTraitsType::HandleType handle) : 
    m_handle(handle) {
    if (handle == HandleTraitsType::INVALID_VALUE) {
            throw HandleTraitsType::ExceptionType(L"Invalid handle value");
    }
}

template <typename HandleTraitsType, typename TracerType>
    requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
Handle<HandleTraitsType, TracerType>::~Handle() {
    if (m_handle != HandleTraitsType::INVALID_VALUE) {
        if (!HandleTraitsType::close(m_handle)) {
            TracerType::exception(HandleTraitsType::ExceptionType(L"Failed closing service handle"));
        }
    }
}

template <typename HandleTraitsType, typename TracerType>
requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
Handle<HandleTraitsType, TracerType>::Handle(Handle<HandleTraitsType, TracerType>&& other) noexcept : 
    m_handle(std::exchange(other.m_handle, HandleTraitsType::INVALID_VALUE)) {
    // Left blank intentionally
}

template <typename HandleTraitsType, typename TracerType>
    requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
Handle<HandleTraitsType, TracerType>
&Handle<HandleTraitsType, TracerType>::operator=(Handle<HandleTraitsType, TracerType>&& other) noexcept {
    m_handle = std::exchange(other.m_handle, HandleTraits::INVALID_VALUE);
    return *this;
}

template <typename HandleTraitsType, typename TracerType>
    requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
Handle<HandleTraitsType, TracerType>::operator typename HandleTraitsType::HandleType() const {
    return m_handle;
}
