#include "Service.h"

#include "Exceptions.h"

using std::wstring;

Service::Service(ServiceHandle serviceHandle) :
    m_handle(std::move(serviceHandle)) {
    // Left blank intentionally
}

void Service::start() {
    if (!StartService(m_handle, 0, nullptr)) {
        throw Win32Exception(L"Failed starting service");
    }
}

void Service::stop() {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(m_handle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        throw Win32Exception(L"Failed stopping service");
    }
}

void Service::remove() {
    if (!DeleteService(m_handle)) {
        throw Win32Exception(L"Failed deleting service");
    }
}
