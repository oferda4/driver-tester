#include "drvut.h"

#include "Device.h"
#include "Fixture.h"
#include "Ioctls.h"

namespace drvut {
namespace internal {

namespace {
constexpr UNICODE_STRING NT_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\TestDriver");
constexpr UNICODE_STRING DOS_DEVICE_NAME = RTL_CONSTANT_STRING(L"\\DosDevices\\TestDriver");

void unloadDriver(PDRIVER_OBJECT DriverObject);
NTSTATUS doNothing(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS deviceControl(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS performIoctl(PIRP irp);
NTSTATUS handleListFixturesIoctl(FixtureInfo* outFixtures, size_t outFixturesLength);
NTSTATUS handleListTestsIoctl(PIRP irp);
NTSTATUS handleRunTestIoctl(PIRP irp);
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

    return STATUS_SUCCESS;
}

namespace {

void unloadDriver(PDRIVER_OBJECT DriverObject) {
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
    if (!deviceObject) {
        return;
    }

    TRACE("Unload Driver\n");
    FixturesManager::destroy();
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
    const auto inBufferLength = irpSp->Parameters.DeviceIoControl.InputBufferLength;
    const auto outBufferLength = irpSp->Parameters.DeviceIoControl.OutputBufferLength;
    
    if (!inBufferLength || !outBufferLength) {
        return STATUS_INVALID_PARAMETER;
    }

    auto inBuffer = irp->AssociatedIrp.SystemBuffer;
    auto outBuffer = irp->AssociatedIrp.SystemBuffer;

    switch (irpSp->Parameters.DeviceIoControl.IoControlCode) {
    case Ioctls::LIST_FIXTURES:
        if (inBuffer || inBufferLength) {
            return STATUS_INVALID_PARAMETER;
        }
        return handleListFixturesIoctl(static_cast<FixtureInfo*>(outBuffer), outBufferLength / sizeof(outBuffer));
    case Ioctls::LIST_TESTS:
        break;
    case Ioctls::RUN_TEST:
        break;
    }

    return STATUS_INVALID_DEVICE_REQUEST;
}

NTSTATUS handleListFixturesIoctl(FixtureInfo* outFixtures, size_t outFixturesLength) {
    const auto fixtures = FixturesManager::instance().listFixtures();
    for (uint32_t index = 0; index < min(fixtures.size(), outFixturesLength); index++) {
        outFixtures[index] = fixtures.at(index);
    }
    return (outFixturesLength < fixtures.size()) ? STATUS_MORE_ENTRIES : STATUS_SUCCESS;
}

NTSTATUS handleListTestsIoctl(PIRP irp) {
    UNREFERENCED_PARAMETER(irp);
}

NTSTATUS handleRunTestIoctl(PIRP irp) {
    UNREFERENCED_PARAMETER(irp);
}

}

}
}