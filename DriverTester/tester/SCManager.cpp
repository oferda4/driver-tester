#include "SCManager.h"

#include "Exceptions.h"

SCManager::SCManager() : m_handle(OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS)) {
	// Left blank intentionally
}

Service SCManager::createService(const std::wstring& name, const std::wstring& pePath) {
	return Service(m_handle, name, pePath);
}
