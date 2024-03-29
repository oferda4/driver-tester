#pragma once

#include "Handle.h"

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::HandleGuard(HandleTraitsType traits, HandleTraitsType::Type handle)
    : m_traits(std::move(traits)), m_handle(handle), m_isValid(true) {
    // intentionally left blank
}

template <HandleTraits HandleTraitsType>
template <typename>
HandleGuard<HandleTraitsType>::HandleGuard(HandleTraitsType::Type handle)
    : HandleGuard(HandleTraitsType(), handle) {
    // intentionally left blank
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::~HandleGuard() {
    destroyIfValid();
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>::HandleGuard(HandleGuard&& other) noexcept
    : m_traits(std::move(other.m_traits)), m_handle(other.m_handle),
      m_isValid(std::exchange(other.m_isValid, false)) {
    // intentionally left blank
}

template <HandleTraits HandleTraitsType>
HandleGuard<HandleTraitsType>&
HandleGuard<HandleTraitsType>::operator=(HandleGuard&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroyIfValid();

    m_traits = std::move(other.m_traits);
    m_handle = other.m_handle;
    m_isValid = std::exchange(other.m_isValid, false);

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

template <HandleTraits HandleTraitsType>
void HandleGuard<HandleTraitsType>::destroyIfValid() {
    if (m_isValid) {
        m_traits.close(m_handle);
    }
}
