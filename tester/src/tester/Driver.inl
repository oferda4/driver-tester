#pragma once

#include "Driver.h"
#include "Safety.h"

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverInstallationGuard<API, Tracer>::DriverInstallationGuard(const std::wstring& name, const std::wstring& pePath) : 
    m_handle(API::create(name, pePath)) {
    // Left blank
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverInstallationGuard<API, Tracer>::~DriverInstallationGuard() {
    if (m_handle.has_value()) {
        Safery::tryExecute([&]() { API::remove(*m_handle); });
    }
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverInstallationGuard<API, Tracer>::operator typename API::HandleType() const {
    return m_handle.value();
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverRunningGuard<API, Tracer>::DriverRunningGuard(typename API::HandleType& driverServiceHandle) : 
        m_driveServiceHandle(driverServiceHandle)  {
    API::start(m_driverServiceHandle);
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverRunningGuard<API, Tracer>::~DriverRunningGuard() {
    Safery::tryExecute([&]() { API::stop(m_driverServiceHandle); });
}