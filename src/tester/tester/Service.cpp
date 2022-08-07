#include "Service.h"

bool ServiceHandleTraits::close(HandleType handle) {
    return CloseServiceHandle(handle);
}

Service::Service(ServiceHandle handle) : m_handle(std::move(handle)) {
    // Left blank intentionally
}

void Service::start() {
    if (!StartService(m_handle, 0, nullptr)) {
        throw WinAPIException(L"Failed starting service");
    }
}

void Service::stop() {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(m_handle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        throw WinAPIException(L"Failed stopping service");
    }
}

void Service::remove() {
    if (!DeleteService(m_handle)) {
        throw WinAPIException(L"Failed deleting service");
    }
}

SCManager::SCManager() : m_handle(OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)) {
    // Left blank intentionally
}

Service SCManager::create(const std::wstring& name, const std::wstring& pePath) {
    return Service(
                ServiceHandle(CreateService(m_handle,
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
                              nullptr)
                )
            );
}

Service SCManager::open(const std::wstring& name) {
    return Service(ServiceHandle(OpenService(m_handle, name.c_str(), SERVICE_ALL_ACCESS)));
}
