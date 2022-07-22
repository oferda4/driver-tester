#pragma once

#include "Resource.h"

namespace drvut {
namespace internal {

template <Resource T>
ResourceGuard<T>::ResourceGuard(T resource, bool isValid) :
    m_resource(std::move(resource)),
    m_isValid(isValid) {
    // Left blank intenrionally
}

template <Resource T>
ResourceGuard<T>::~ResourceGuard() {
    if (m_isValid) {
        // TODO: Trace errors
        m_resource.destroy();
    }
}

template <Resource T>
ResourceGuard<T>::ResourceGuard(ResourceGuard&& other) :
    m_resource(std::move(other.m_resource)),
    m_isValid(std::exchange(other.m_isValid, false)) {
    // Left blank intenrionally
}

template <Resource T>
ResourceGuard<T>& ResourceGuard<T>::operator=(ResourceGuard&& other) {
    m_resource = std::move(other.m_resource);
    m_isValid = std::exchange(other.m_isValid, false);
    return *this;
}

template <Resource T>
NTSTATUS ResourceGuard<T>::init() {
    if (m_isValid) {
        ExRaiseStatus(STATUS_INVALID_STATE_TRANSITION);
    }

    const NTSTATUS status = m_resource.initialize();
    CHECK_AND_RETHROW(status);
    m_isValid = true;
    return status;
}

template <Resource T>
T& ResourceGuard<T>::get() {
    if (!m_isValid) {
        ExRaiseStatus(STATUS_INVALID_STATE_TRANSITION);
    }
    return m_resource;
}

template <Resource T>
const T& ResourceGuard<T>::get() const {
    if (!m_isValid) {
        ExRaiseStatus(STATUS_INVALID_STATE_TRANSITION);
    }
    return m_resource;
}

template <Resource T>
void ResourceGuard<T>::leak() {
    m_isValid = false;
}

}
}
