#include "ServiceController.h"

bool WinServiceAPI::start(ServiceHandle handle) {
    return StartService(handle, 0, nullptr);
}

bool WinServiceAPI::stop(ServiceHandle handle) {
    SERVICE_STATUS serviceStatus;
    return ControlService(handle, SERVICE_CONTROL_STOP, &serviceStatus);
}

bool WinServiceAPI::remove(ServiceHandle handle) {
    return DeleteService(handle);
}

bool ServiceHandleTraits::close(HandleType handle) {
    return CloseServiceHandle(handle);
}
