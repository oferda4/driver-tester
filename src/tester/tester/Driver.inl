#pragma once

#include "Driver.h"
#include "Safety.h"

template <ExceptionTracer Tracer>
DriverInstallationGuard<Tracer>::DriverInstallationGuard(SCManager& manager, const std::wstring& name, const std::wstring& pePath) : 
    m_service(std::make_unique<Service>(manager.create(name, pePath))) {
    // Left blank intentionally
}

template <ExceptionTracer Tracer>
DriverInstallationGuard<Tracer>::~DriverInstallationGuard() {
    if (m_service) {
        Safety::tryExecute<Tracer>([&]() { m_service->remove(); });
    }
}

template <ExceptionTracer Tracer>
Service& DriverInstallationGuard<Tracer>::get() {
    if (!m_service) {
        throw std::exception("Invalid state");
    }
    return *m_service;
}

template <ExceptionTracer Tracer>
DriverRunningGuard<Tracer>::DriverRunningGuard(Service& driverService) : 
        m_driverService(driverService) {
    m_driverService.start();
}

template <ExceptionTracer Tracer>
DriverRunningGuard<Tracer>::~DriverRunningGuard() {
    Safety::tryExecute<Tracer>([&]() { m_driverService.stop(); });
}