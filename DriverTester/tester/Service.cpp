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
        traceException("Failed deleting service");
    }
}

void tryStopService(const ServiceHandle& handle) {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(handle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        traceException("Failed stopping service");
    }
}

void Service::start() {
    if (!StartService(*m_handle, 0, nullptr)) {
        throw Win32Exception("Failed starting service");
    }
    isStarted = true;
}
