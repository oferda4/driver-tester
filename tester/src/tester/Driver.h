#pragma once

#include <optional>

#include "Service.h"

/**
 * We install drivers in the classic way of creating a service.
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

#include "Driver.inl"
