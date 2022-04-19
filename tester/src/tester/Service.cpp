#include "Service.h"

WinServiceController::WinServiceController(ServiceHandle handle) : m_handle(std::move(handle)) {
    // Left blank
}

bool WinServiceController::start() {
    return StartService(m_handle, 0, nullptr);
}

bool WinServiceController::stop() {
    SERVICE_STATUS serviceStatus;
    return ControlService(m_handle, SERVICE_CONTROL_STOP, &serviceStatus);
}

bool WinServiceController::remove() {
    return DeleteService(m_handle);
}

bool ServiceHandleTraits::close(HandleType handle) {
    return CloseServiceHandle(handle);
}
