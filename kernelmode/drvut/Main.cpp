#include "drvut/Test.h"
#include "drvut/drvut.h"
#include "drvut/internal/Device.h"
#include "drvut/internal/Error.h"
#include "drvut/internal/IoctlHandler.h"

namespace drvut {
namespace internal {

namespace {
constexpr UNICODE_STRING NT_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\TestDriver");
constexpr UNICODE_STRING DOS_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\DosDevices\\TestDriver");

void unloadDriver(PDRIVER_OBJECT DriverObject);
NTSTATUS doNothing(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS deviceControl(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS performIoctl(PIRP irp);
}

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DeviceGuard device(Device(DriverObject, &NT_DEVICE_NAME));
    SymbolicLinkGuard symbolicLink(SymbolicLink(&DOS_DEVICE_NAME, &NT_DEVICE_NAME));

    TRACE("Driver Entry\n");

    DriverObject->MajorFunction[IRP_MJ_CREATE] = doNothing;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = doNothing;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = deviceControl;
    DriverObject->DriverUnload = unloadDriver;

    CHECK_AND_RETHROW(device.init());
    CHECK_AND_RETHROW(symbolicLink.init());

    symbolicLink.leak();
    device.leak();
    ErrorMessage::initialize();

    initializeTests();

    return STATUS_SUCCESS;
}

namespace {

void unloadDriver(PDRIVER_OBJECT DriverObject) {
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
    if (!deviceObject) {
        return;
    }

    TRACE("Unload Driver\n");
    TestsManager::destroy();
    ErrorMessage::destroy();
    DeviceGuard device(Device(deviceObject), true);
    SymbolicLinkGuard symbolicLink(SymbolicLink(&DOS_DEVICE_NAME), true);
}

NTSTATUS doNothing(PDEVICE_OBJECT deviceObject, PIRP irp) {
    UNREFERENCED_PARAMETER(deviceObject);

    irp->IoStatus.Status = STATUS_SUCCESS;
    irp->IoStatus.Information = 0;

    IoCompleteRequest(irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS deviceControl(PDEVICE_OBJECT deviceObject, PIRP irp) {
    UNREFERENCED_PARAMETER(deviceObject);
    const NTSTATUS result = performIoctl(irp);

    irp->IoStatus.Status = result;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return result;
}

NTSTATUS performIoctl(PIRP irp) {
    auto irpSp = IoGetCurrentIrpStackLocation(irp);
    const auto inputBufferLength = irpSp->Parameters.DeviceIoControl.InputBufferLength;
    const auto outputBufferLength = irpSp->Parameters.DeviceIoControl.OutputBufferLength;

    auto inputBuffer = irp->AssociatedIrp.SystemBuffer;
    auto outputBuffer = irp->AssociatedIrp.SystemBuffer;

    const auto result = IoctlHandler::handle(
        TestsManager::instance(), irpSp->Parameters.DeviceIoControl.IoControlCode,
        BufferView(inputBuffer, inputBufferLength), BufferView(outputBuffer, outputBufferLength));

    if (NT_SUCCESS(result)) {
        irp->IoStatus.Information = outputBufferLength;
    }

    return result;
}

}

}
}