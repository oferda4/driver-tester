#pragma once

#include "Driver.h"
#include "Safety.h"

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

template <typename API, typename Tracer>
    requires ServiceControlAPI<API> && ExceptionTracer<Tracer>
DriverRunningGuard<API, Tracer>::DriverRunningGuard(typename API::HandleType& driverServiceHandle) : 
        m_driveServiceHandle(driverServiceHandle)  {
    API::start(m_driverServiceHandle);
}

template <typename API, typename Tracer>
    requires ServiceControlAPI<API> && ExceptionTracer<Tracer>
DriverRunningGuard<API, Tracer>::~DriverRunningGuard() {
    Safery::tryExecute([&]() { API::stop(m_driverServiceHandle); });
}