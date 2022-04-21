#pragma once

#include "Driver.h"

template <typename API>
    requires ServiceAPI<API>
DriverInstallationGuard<API>::DriverInstallationGuard(const std::wstring& name, const std::wstring& pePath) : 
    m_handle(API::create(name, pePath)) {
    // Left blank
}

template <typename API>
    requires ServiceAPI<API>
DriverInstallationGuard<API>::~DriverInstallationGuard() {
    if (m_handle.has_value()) {
        API::remove(*m_handle);
    }
}

template <typename API>
    requires ServiceAPI<API>
DriverInstallationGuard<API>::operator typename API::HandleType() const {
    return m_handle.value();
}