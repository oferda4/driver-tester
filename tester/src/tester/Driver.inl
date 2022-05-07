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
        Safety::tryExecute<Tracer>([&]() { API::remove(*m_handle); });
    }
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverInstallationGuard<API, Tracer>::operator typename API::HandleType&() {
    return m_handle.value();
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverRunningGuard<API, Tracer>::DriverRunningGuard(typename API::HandleType& driverServiceHandle) : 
        m_driverServiceHandle(driverServiceHandle) {
    API::start(m_driverServiceHandle);
}

template <ServiceControlAPI API, ExceptionTracer Tracer>
DriverRunningGuard<API, Tracer>::~DriverRunningGuard() {
    Safety::tryExecute<Tracer>([&]() { API::stop(m_driverServiceHandle); });
}