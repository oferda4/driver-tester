#include "drvut.h"

#include "Device.h"

namespace drvut {
namespace internal {

static constexpr UNICODE_STRING NT_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\TestDriver");
static constexpr UNICODE_STRING DOS_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\DosDevices\\TestDriver");

static void unloadDriver(PDRIVER_OBJECT DriverObject);

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    NTSTATUS status;
    DeviceGuard device(Device(DriverObject, &NT_DEVICE_NAME));
    
    UNREFERENCED_PARAMETER(RegistryPath);

    TRACE("Driver Entry\n");

    status = device.init();
    if (!NT_SUCCESS(status)) {
        TRACE("Couldn't create the device object\n");
        return status;
    }

    DriverObject->DriverUnload = unloadDriver;

    status = IoCreateSymbolicLink(const_cast<PUNICODE_STRING>(&DOS_DEVICE_NAME), const_cast<PUNICODE_STRING>(&NT_DEVICE_NAME));
    if (!NT_SUCCESS(status)) {
        TRACE("Couldn't create symbolic link\n");
        return status;
    }

    device.leak();

    return status;
}

void unloadDriver(PDRIVER_OBJECT DriverObject) {
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
    
    PAGED_CODE();

    TRACE("Unload Driver\n");
    IoDeleteSymbolicLink(const_cast<PUNICODE_STRING>(&DOS_DEVICE_NAME));
    if (deviceObject) {
        DeviceGuard device(Device(deviceObject), true);
    }
}

}
}