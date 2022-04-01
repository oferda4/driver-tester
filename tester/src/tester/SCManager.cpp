#include "SCManager.h"

#include "Exceptions.h"

SCManager::SCManager() : m_handle(OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)) {
    // Left blank intentionally
}

Service SCManager::createService(const std::wstring& name, const std::wstring& pePath) {
    return { CreateService(m_handle,
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
        nullptr) };
}

Service SCManager::openService(const std::wstring& name) {
    return { OpenService(m_handle, name.c_str(), SERVICE_ALL_ACCESS) };
}
