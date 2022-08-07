#pragma once

#include <optional>

#include "Service.h"
#include "Exceptions.h"

/**
 * We install drivers in the classic way of creating a service.
 * Then running it by starting the service.
 */

template <ExceptionTracer Tracer>
class DriverInstallationGuard final {
public:
    DriverInstallationGuard(SCManager& manager, const std::wstring& name, const std::wstring& pePath);
    ~DriverInstallationGuard();
    NOCOPY(DriverInstallationGuard);
    MOVEABLE(DriverInstallationGuard);

    Service& get();

private:
    std::unique_ptr<Service> m_service;
};

template <ExceptionTracer Tracer>
class DriverRunningGuard final {
public:
    DriverRunningGuard(Service& driverService);
    ~DriverRunningGuard();
    NOCOPY(DriverRunningGuard);
    NOMOVE(DriverRunningGuard);

private:
    Service& m_driverService;
};

#include "Driver.inl"
