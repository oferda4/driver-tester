#pragma once

#include <optional>

#include "Service.h"
#include "Exceptions.h"

/**
 * We install drivers in the classic way of creating a service.
 * Then running it by starting the service.
 */

template <typename API>
	requires ServiceAPI<API>
class DriverInstallationGuard final {
public:
    DriverInstallationGuard(const std::wstring& name, const std::wstring& pePath);
    ~DriverInstallationGuard();
    NOCOPY(DriverInstallationGuard);
    MOVEABLE(DriverInstallationGuard);

    operator typename API::HandleType() const;

private:
    std::optional<typename API::HandleType> m_handle;
};

template <typename API, typename Tracer>
    requires ServiceControlAPI<API> && ExceptionTracer<Tracer>
class DriverRunningGuard final {
public:
    DriverRunningGuard(typename API::HandleType& driverServiceHandle);
    ~DriverRunningGuard();
    NOCOPY(DriverRunningGuard);
    NOMOVE(DriverRunningGuard);

private:
    typename API::driverServiceHandle& m_driverServiceHandle;
};

#include "Driver.inl"
