#pragma once

#include "Handle.h"

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::HandleGuard(HandleTraitsType traits, HandleTraitsType::Type handle) 
    : m_traits(std::move(traits)), m_handle(handle), m_isValid(true) {
    // left blank intentionally
}

template <HandleTraits HandleTraitsType>
template <typename>
HandleGuard<HandleTraitsType>::HandleGuard(HandleTraitsType::Type handle) 
    : HandleGuard(HandleTraitsType(), handle) {
    // left blank intentionally
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::~HandleGuard() {
    if (m_isValid) {
        m_traits.close(m_handle);
    }
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::HandleGuard(HandleGuard&& other) noexcept
    : m_traits(std::move(other.m_traits)), m_handle(other.m_handle), m_isValid(std::exchange(other.m_isValid, false)) {
    // left blank intentionally
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>& HandleGuard<HandleTraitsType>::operator=(HandleGuard&& other) noexcept {
    if (this != &other) {
        m_traits = std::move(other.m_traits);
        m_handle = other.m_handle;
        m_isValid = std::exchange(other.m_isValid, false);
    }
    return *this;
}

template <HandleTraits HandleTraitsType>
typename HandleTraitsType::Type HandleGuard<HandleTraitsType>::operator*() {
    validate();
    return m_handle;
}

template <HandleTraits HandleTraitsType>
const typename HandleTraitsType::Type HandleGuard<HandleTraitsType>::operator*() const {
    validate();
    return m_handle;
}

template <HandleTraits HandleTraitsType>
void HandleGuard<HandleTraitsType>::validate() const {
    if (!m_isValid) {
        throw InvalidHandle();
    }
}
