#include "drvut.h"

#include "Device.h"

namespace drvut {
namespace internal {

static constexpr UNICODE_STRING NT_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\TestDriver");
static constexpr UNICODE_STRING DOS_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\DosDevices\\TestDriver");

static void unloadDriver(PDRIVER_OBJECT DriverObject);

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DeviceGuard device(Device(DriverObject, &NT_DEVICE_NAME));
    SymbolicLinkGuard symbolicLink(SymbolicLink(&DOS_DEVICE_NAME, &NT_DEVICE_NAME));

    TRACE("Driver Entry\n");
    DriverObject->DriverUnload = unloadDriver;
    CHECK_AND_RETHROW(device.init());
    CHECK_AND_RETHROW(symbolicLink.init());

    symbolicLink.leak();
    device.leak();

    return STATUS_SUCCESS;
}

void unloadDriver(PDRIVER_OBJECT DriverObject) {
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
    if (!deviceObject) {
        return;
    }

    TRACE("Unload Driver\n");
    DeviceGuard device(Device(deviceObject), true);
    SymbolicLinkGuard symbolicLink(SymbolicLink(&DOS_DEVICE_NAME), true);
}

}
}