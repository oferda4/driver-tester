#include "Service.h"

#include "Exceptions.h"

using std::wstring;

static void tryDeleteService(const ServiceHandle& handle);
static void tryStopService(const ServiceHandle& handle);

Service::Service(ServiceHandle serviceHandle) :
    m_handle(std::move(serviceHandle)),
    isStarted(false) {
    // Left blank intentionally
}

Service::~Service() {
    if (m_handle.has_value()) {
        if (isStarted) {
            tryStopService(*m_handle);
        }
        tryDeleteService(*m_handle);
    }
}

void tryDeleteService(const ServiceHandle& handle) {
    if (DeleteService(handle)) {
        traceError(L"Failed deleting service");
    }
}

void tryStopService(const ServiceHandle& handle) {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(handle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        traceError(L"Failed stopping service");
    }
}

void Service::start() {
    if (!StartService(*m_handle, 0, nullptr)) {
        throw Win32Exception(L"Failed starting service");
    }
    isStarted = true;
}
