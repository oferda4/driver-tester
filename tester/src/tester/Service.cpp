#include "Service.h"

void WinServiceAPI::start(HandleType& handle) {
    if (!StartService(handle, 0, nullptr)) {
        throw WinAPIException(L"Failed starting service");
    }
}

void WinServiceAPI::stop(HandleType& handle) {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(handle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        throw WinAPIException(L"Failed stopping service");
    }
}

void WinServiceAPI::remove(HandleType& handle) {
    if (!DeleteService(handle)) {
        throw WinAPIException(L"Failed deleting service");
    }
}

WinServiceAPI::HandleType WinServiceAPI::create(const std::wstring& name, const std::wstring& pePath) {
    return SCManager().create(name, pePath);
}

WinServiceAPI::HandleType WinServiceAPI::open(const std::wstring& name) {
    return SCManager().open(name);
}

bool ServiceHandleTraits::close(HandleType handle) {
    return CloseServiceHandle(handle);
}

SCManager::SCManager() : m_handle(OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)) {
    // Left blank intentionally
}

ServiceHandle SCManager::create(const std::wstring& name, const std::wstring& pePath) {
    return CreateService(m_handle,
                         name.c_str(),
                         name.c_str(),
                         SERVICE_ALL_ACCESS,
                         SERVICE_KERNEL_DRIVER,
                         SERVICE_DEMAND_START,
                         SERVICE_ERROR_NORMAL,
                         pePath.c_str(),
                         nullptr,
                         nullptr,
                         nullptr,
                         nullptr,
                         nullptr);
}

ServiceHandle SCManager::open(const std::wstring& name) {
    return OpenService(m_handle, name.c_str(), SERVICE_ALL_ACCESS);
}
