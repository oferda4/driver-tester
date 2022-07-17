#include "drvut.h"

static constexpr UNICODE_STRING NT_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\TestDriver");
static constexpr UNICODE_STRING DOS_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\DosDevices\\TestDriver");

static void unloadDriver(PDRIVER_OBJECT DriverObject);

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    NTSTATUS status;
    PDEVICE_OBJECT deviceObject = NULL;

    UNREFERENCED_PARAMETER(RegistryPath);

    TRACE("Driver Entry\n");

    status = IoCreateDevice(DriverObject, 0, const_cast<PUNICODE_STRING>(&NT_DEVICE_NAME), FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObject);

    if (!NT_SUCCESS(status)) {
        TRACE("Couldn't create the device object\n");
        return status;
    }

    DriverObject->DriverUnload = unloadDriver;

    status = IoCreateSymbolicLink(const_cast<PUNICODE_STRING>(&DOS_DEVICE_NAME), const_cast<PUNICODE_STRING>(&NT_DEVICE_NAME));

    if (!NT_SUCCESS(status)) {
        TRACE("Couldn't create symbolic link\n");
        IoDeleteDevice(deviceObject);
    }

    return status;
}

void unloadDriver(PDRIVER_OBJECT DriverObject) {
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
    
    PAGED_CODE();

    TRACE("Unload Driver\n");
    IoDeleteSymbolicLink(const_cast<PUNICODE_STRING>(&DOS_DEVICE_NAME));
    if (deviceObject) {
        IoDeleteDevice(deviceObject);
    }
}