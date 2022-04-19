#include "ServiceManager.h"

#include "Exceptions.h"

SCManager::SCManager() : m_handle(OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)) {
    // Left blank intentionally
}

WinService SCManager::create(const std::wstring& name, const std::wstring& pePath) {
    return createServiceObject(CreateService(m_handle,
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
                                             nullptr));
}

WinService SCManager::open(const std::wstring& name) {
    return createServiceObject(OpenService(m_handle, name.c_str(), SERVICE_ALL_ACCESS));
}

WinService SCManager::createServiceObject(ServiceHandle serviceHandle) {
    return WinService(WinServiceController(std::move(serviceHandle)));
}
