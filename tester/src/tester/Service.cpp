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

bool ServiceHandleTraits::close(HandleType handle) {
    return CloseServiceHandle(handle);
}
