#pragma once

#include <optional>

#include "Service.h"
#include "Exceptions.h"

/**
 * We install drivers in the classic way of creating a service.
 * Then running it by starting the service.
 */

template <ServiceControlAPI API, ExceptionTracer Tracer>
class DriverInstallationGuard final {
public:
    DriverInstallationGuard(const std::wstring& name, const std::wstring& pePath);
    ~DriverInstallationGuard();
    NOCOPY(DriverInstallationGuard);
    MOVEABLE(DriverInstallationGuard);

    operator typename API::HandleType&();

private:
    std::optional<typename API::HandleType> m_handle;
};

template <ServiceControlAPI API, ExceptionTracer Tracer>
class DriverRunningGuard final {
public:
    DriverRunningGuard(typename API::HandleType& driverServiceHandle);
    ~DriverRunningGuard();
    NOCOPY(DriverRunningGuard);
    NOMOVE(DriverRunningGuard);

private:
    typename API::HandleType& m_driverServiceHandle;
};

#include "Driver.inl"
